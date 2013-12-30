/*
 * =====================================================================================
 *
 *       Filename:  09_pipe.c
 *
 *    Description: 
 *
 *        Version:  1.0
 *        Created:  06/08/13 00:40:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

static void sig_pipe(int);/*our signal handler*/

int main(void){
	int n, fd1[2], fd2[2];
	FILE *fpin,*fpout;
	pid_t pid;
	char line[MAXLINE];

	if(signal(SIGPIPE, sig_pipe) == SIG_ERR)
		err_sys("signal error");

	if(pipe(fd1) < 0 || pipe(fd2) < 0)
		err_sys("pipe error");

	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid > 0){/*parent*/
		close(fd1[0]);/*close fd1 read, open fd1 write*/
		close(fd2[1]);/*close fd2 write, open fd2 read*/

		/*associate a stream with a file descriptor*/
		if((fpin = fdopen(fd2[0], "r")) == NULL)
			err_sys("fdopen error");
		if((fpout = fdopen(fd1[1], "w")) == NULL)
			err_sys("fdopen error");
		/*set io_buf*/
		if(setvbuf(fpin, NULL, _IOLBF, 0) < 0)
			err_sys("setvbuf error");
		if(setvbuf(fpout, NULL, _IOLBF, 0) < 0)
			err_sys("setvbuf error");

		while(fgets(line, MAXLINE, stdin) != NULL){
			n = strlen(line);
			printf("read line:%s", line);
			if(fputs(line, fpout) == EOF){
				err_sys("fputs error to pipe");
			}
			if((fgets(line, MAXLINE, fpin)) == NULL){
				err_sys("child closed pipe");
				break;
			}
			if(fputs(line, stdout) == EOF)
				err_sys("fputs error");
		}
		if(ferror(stdin)){
			err_sys("fgets error on stdin");
		}
		exit(0);
	}else{/*child*/
		close(fd1[1]);/*close fd1 write, open fd1 read*/
		/*close(fd1[0]);*//*close fd1 read, catch pipe signal*/
		close(fd2[0]);/*close fd2 read, open fd2 write*/

		if(fd1[0]!=STDIN_FILENO){
			if(dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)
				err_sys("dup2 error to stdin");
			close(fd1[0]);
		}
		if(fd2[1]!=STDOUT_FILENO){
			if(dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
				err_sys("dup2 error to stdout");
			close(fd2[1]);
		}
		/*if(execl("./05_add", "05_add", (char *)0) < 0)*/
		if(execl("./05_addstdio", "05_add", (char *)0) < 0)
			err_sys("execl error");
	}
	exit(0);
}

static void sig_pipe(int signo){
	printf("%d SIGPIPE caught\n",getpid());
	exit(1);
}
