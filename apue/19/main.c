/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  pty main.
 *
 *        Version:  1.0
 *        Created:  06/25/13 23:52:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<termios.h>
#include<sys/select.h>
#include<poll.h>
#ifndef TIOCGWINSZ
#include <sys/ioctl.h> /*for struct winsize*/
#endif

#ifdef LINUX
#define OPTSTR "d:einv"
#else
#define OPTSTR "d:einv"
#endif

pid_t pty_fork(int *, char *, int, const struct termios *, const struct winsize *);
static void set_noecho(int);/*at the end of this file*/
void do_driver(char *);/*int the file driver.c*/
void loop(int, int);/*in the file loop.c*/

int main(int argc, char *argv[]){
	int fdm, c, ignoreeof, interactive, noecho, verbose;
	pid_t pid;
	char *driver;
	char slave_name[20];
	struct termios orig_termios;
	struct winsize size;

	interactive = isatty(STDIN_FILENO);
	ignoreeof = 0;
	noecho = 0;
	verbose = 0;
	driver = NULL;

	opterr = 0;/*don't want getopt() writing to stderr*/
	printf("ifdef LINUX = %d, interactive = %d\n", LINUX, interactive);
	/*OPTSTR in top define.*/
	while((c = getopt(argc, argv, OPTSTR)) != EOF){
		switch(c){
			case 'd': /*driver for stdin/stdout*/
				driver = optarg;
				break;
			case 'e': /*noecho for slave pty's line disclipline*/
				noecho = 1;
				break;
			case 'i': /*ignore EOF on standard input*/
				ignoreeof = 1;
				break;
			case 'n': /*not interactive*/
				interactive = 0;
				break;
			case 'v': /*verbose*/
				verbose = 1;
				break;
			case '?':
				err_quit("unrecognized option: -%c", optopt);
		}
	}
	printf("optind = %d, optarg = %s, argv = %s\n", optind, optarg, argv[optind]);
	if(optind >= argc)
		err_quit("usage: pty [ -d driver -einv ] program [ arg ... ]");

	if(interactive){/*fetch current termios and window size*/
		if(tcgetattr(STDIN_FILENO, &orig_termios) < 0)
			err_sys("tcgetattr error on stdin");
		if(ioctl(STDIN_FILENO, TIOCGWINSZ, (char *)&size) < 0)
			err_sys("TIOCGWINSZ error");
		printf("%d rows, %d columns\n", size.ws_row, size.ws_col);
		pid = pty_fork(&fdm, slave_name, sizeof(slave_name), &orig_termios, &size);
	}else{
		pid = pty_fork(&fdm, slave_name, sizeof(slave_name), NULL, NULL);
	}
	system("ps -o pid,ppid,pgid,sid,comm,stat,fname,tty");
	/*sleep(1);*/
	/*printf("slave_name:%s\n", slave_name);*/
	if(pid < 0)
		err_sys("fork error");
	else if(pid == 0){/*child*/
		if(noecho)
			set_noecho(STDIN_FILENO);/*stdin is salve pty*/
		/*printf("optind:%d,argv:%s\n", optind, argv[optind]);*/
		if(execvp(argv[optind], &argv[optind]) < 0)
			err_sys("can't execute: %s", argv[optind]);
	}
	/*parent*/
	if(verbose){
		fprintf(stderr, "slave name = %s\n", slave_name);
		if(driver != NULL)
			fprintf(stderr, "driver = %s\n", driver);
	}

	if(interactive && driver == NULL){
		if(tty_raw(STDIN_FILENO) < 0) /*user's tty to raw mode*/
			err_sys("tty_raw error");
		if(atexit(tty_atexit) < 0) /*reset user's tty on exit*/
			err_sys("atexit error");
	}

	if(driver)
		do_driver(driver);/*changes our stdin/stdout*/

	loop(fdm, ignoreeof);/*copies stdin > ptym, ptym->stdout*/
	exit(0);
}

static void set_noecho(int fd){/*turn off echo (for slave pty)*/
	struct termios stermios;

	if(tcgetattr(fd, &stermios) < 0)
		err_sys("tcgetattr error");

	stermios.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);

	/*
	 * Also turn off NL to CR/NL mapping on output.
	 */
	stermios.c_oflag &= ~(ONLCR);

	if(tcsetattr(fd, TCSANOW, &stermios) < 0)
		err_sys("tcsetattr error");
}

/*
 * Start do_driver function
 */
void do_driver(char *driver){
	pid_t child;
	int pipe[2];

	/*
	 * Create a stream pipe to communicate with the driver
	 */
	if(s_pipe(pipe) < 0){
		err_sys("can't create stream pipe");
	}

	if((child = fork()) < 0){
		err_sys("fork error");
	}else if(child == 0){/*child*/
		close(pipe[1]);/*close the write term.*/

		/*stdin for driver*/
		if(dup2(pipe[0], STDIN_FILENO) != STDIN_FILENO)
			err_sys("dup2 error to stdin");
		/*stdout for driver*/
		if(dup2(pipe[0], STDOUT_FILENO) != STDOUT_FILENO)
			err_sys("dup2 error to stdout");
		if(pipe[0] != STDIN_FILENO && pipe[0] != STDOUT_FILENO)
			close(pipe[0]);
		
		/*leave stderr for driver alone*/
		execlp(driver, driver, (char *)0);
		err_sys("execlp error for: %s", driver);
	}
	close(pipe[0]);/*parent close read term.*/
	if(dup2(pipe[1], STDIN_FILENO) != STDIN_FILENO)
		err_sys("dup2 error to stdin");
	if(dup2(pipe[1], STDOUT_FILENO) != STDOUT_FILENO)
		err_sys("dup2 error to stdout");
	if(pipe[1] != STDIN_FILENO && pipe[1] != STDOUT_FILENO)
		close(pipe[1]);
	
	/*
	 * Parent returns, but with stdin and stdout connected
	 * to the driver.
	 */
}

/*
 * Start loop function.
 */
#define BUFFSIZE 512
static void sig_term(int);
static volatile sig_atomic_t sigcaught;/*set by signal handler*/

/*use poll to select*/
void poll_loop(int ptym, int ignoreeof){
	int nread, maxi;
	char buf[BUFFSIZE];
	struct pollfd *pollfd;

	if((pollfd = malloc(open_max() * sizeof(struct pollfd))) == NULL)
		err_sys("malloc error");


	maxi = 4;
	for(;;){
		pollfd[0].fd = STDIN_FILENO;
		pollfd[0].events = POLLIN;
		pollfd[1].fd = ptym;
		pollfd[1].events = POLLIN;

		pollfd[2].fd = STDOUT_FILENO;
		pollfd[2].events = POLLOUT;
		pollfd[3].fd = ptym;
		pollfd[3].events = POLLOUT;

		if(poll(pollfd, maxi+1, -1)<0)
			err_sys("poll error");

		if((pollfd[0].revents & POLLIN) && (pollfd[3].revents & POLLOUT)){
			if((nread = read(STDIN_FILENO, buf, BUFFSIZE)) < 0){
				err_sys("read error from stdin");
			}else if(nread == 0){
				break;/*EOF on stdin means we're done*/
			}
			/*write(STDOUT_FILENO, "from child:", 11);*/
			if(writen(ptym, buf, nread) != nread){
				err_sys("writen error to master pty");
			}
		}
		if((pollfd[1].revents & POLLIN) && (pollfd[2].revents & POLLOUT)){
			if((nread = read(ptym, buf, BUFFSIZE)) <= 0){
				printf("parent read EOF\n");
				break;/*signal caught, error, or EOF*/
			}
			/*write(STDOUT_FILENO, "from parent:", 13);*/
			if(writen(STDOUT_FILENO, buf, nread) != nread){
				err_sys("writen error to stdout");
			}
		}
	}
}

/*use select to loop*/
void loop(int ptym, int ignoreeof){
	int nread,maxfd;
	char buf[BUFFSIZE];
	fd_set readset, writeset;
	
	/*printf("ignoreeof:%d\n", ignoreeof);*/
	for(;;){
		FD_ZERO(&readset);
		FD_SET(STDIN_FILENO,&readset);
		FD_SET(ptym,&readset);
	
		FD_ZERO(&writeset);
		FD_SET(STDOUT_FILENO,&writeset);
		FD_SET(ptym,&writeset);

		maxfd = ptym+1;
		if(select(maxfd, &readset, &writeset, NULL, NULL)<0)
			err_sys("select error");
		if(FD_ISSET(ptym, &writeset) && FD_ISSET(STDIN_FILENO, &readset)){
			if((nread = read(STDIN_FILENO, buf, BUFFSIZE)) < 0){
				err_sys("read error from stdin");
			}else if(nread == 0){
				break;/*EOF on stdin means we're done*/
			}
			/*write(STDOUT_FILENO, "from child:", 11);*/
			if(writen(ptym, buf, nread) != nread){
				err_sys("writen error to master pty");
			}
		}
		if(FD_ISSET(ptym, &readset) && FD_ISSET(STDOUT_FILENO, &writeset)){
			if((nread = read(ptym, buf, BUFFSIZE)) <= 0){
				printf("parent read EOF\n");
				break;/*signal caught, error, or EOF*/
			}
			/*write(STDOUT_FILENO, "from parent:", 13);*/
			if(writen(STDOUT_FILENO, buf, nread) != nread){
				err_sys("writen error to stdout");
			}
		}
	}
}

void fork_loop(int ptym, int ignoreeof){
	pid_t child;
	int nread;
	char buf[BUFFSIZE];
	
	/*printf("ignoreeof:%d\n", ignoreeof);*/
	if((child = fork()) < 0){
		err_sys("fork error");
	}else if(child == 0){/*child copies stdin to ptym*/
		/*exit(0);*/
		for(;;){
			if((nread = read(STDIN_FILENO, buf, BUFFSIZE)) < 0){
				err_sys("read error from stdin");
			}else if(nread == 0){
				if(write(STDOUT_FILENO, "child read EOF\n", 16) != 16)
					err_sys("writen error to master pty");
				break;/*EOF on stdin means we're done*/
			}
			/*write(STDOUT_FILENO, "from child:", 11);*/
			if(writen(ptym, buf, nread) != nread){
				err_sys("writen error to master pty");
			}
		}
		/*
		 * We always terminate when we encounter an EOF on stdin,
		 * but we notify the parent only if ignoreeof is 0.
		 */
		if(ignoreeof == 0){
			kill(getppid(), SIGTERM);/*notify parent*/
		}
		exit(0);/*and terminate; child can't return*/
	}
	/*
	 * Parent copies ptym to stdout
	 */
	if(signal_intr(SIGTERM, sig_term) == SIG_ERR)
		err_sys("signal_intr error for SIGTERM");
	for(;;){
		if((nread = read(ptym, buf, BUFFSIZE)) <= 0){
			printf("parent read EOF\n");
			break;/*signal caught, error, or EOF*/
		}
		/*write(STDOUT_FILENO, "from parent:", 13);*/
		if(writen(STDOUT_FILENO, buf, nread) != nread){
			err_sys("writen error to stdout");
		}
	}
	/*
	 * There are three ways to get here: sig_term() below caught the
	 * SIGTERM from the child, we read an EOF on the pty master (which
	 * means we have to signal the child to stop), or an error.
	 */
	if(sigcaught == 0) /*tell child if it didn't send us the signal*/
		kill(child, SIGTERM);
	/*
	 * Parent returns to caller.
	 */
}

/*
 * The child sends us SIGTERM when it gets EOF on the pty slave or
 * when read() fails. We probably interrupted the read() of ptym.
 */
static void sig_term(int signo){
	sigcaught = 1;/*just set flag and return*/
}
