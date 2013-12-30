/*
 * =====================================================================================
 *
 *       Filename:  system.c
 *
 *    Description:  my system function
 *
 *        Version:  1.0
 *        Created:  05/11/13 16:56:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<sys/wait.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

/*system new*/
int my_system(const char *cmdstring){/*with appropriate signal handling*/
	pid_t pid;
	int status;
	struct sigaction ignore, saveintr, savequit;
	sigset_t chldmask, savemask;
	
	if(cmdstring==NULL){
		return(1);/*always a command processor with UNIX*/
	}

	ignore.sa_handler = SIG_IGN;/*ignore SIGINT and SIGQUIT*/
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;
	if(sigaction(SIGINT, &ignore, &saveintr) < 0)
		return(-1);
	if(sigaction(SIGQUIT, &ignore, &savequit) < 0)
		return(-1);
	sigemptyset(&chldmask);/*now block SIGCHLD*/
	sigaddset(&chldmask, SIGCHLD);
	if(sigprocmask(SIG_BLOCK, &chldmask, &savemask) < 0)
		return -1;

	if((pid=fork())<0){
		status = -1;/*probably out of processes*/
	}else if(pid==0){/*child process*/
		/*restore previous signal actions & reset signal mask*/
		sigaction(SIGINT, &saveintr, NULL);
		sigaction(SIGQUIT, &savequit, NULL);
		sigprocmask(SIG_SETMASK, &savemask, NULL);
		execl("/bin/bash", "bash", "-c", cmdstring, NULL);
		_exit(127);/*execl error*/
	}else{/*parent*/
		while(waitpid(pid, &status, 0) < 0){
			if(errno!=EINTR){
				status = -1;/*error other than EINTR from waitpid()*/
				break;
			}
		}
		printf("waitpid = %d\n", pid);
	}
	/*restore previous signal actions & reset signal mask*/
	if(sigaction(SIGINT, &saveintr, NULL) < 0)
		return -1;
	if(sigaction(SIGQUIT, &savequit, NULL) < 0)
		return -1;
	printf("before unblock SIGCHLD\n");
	if(sigprocmask(SIG_SETMASK, &savemask, NULL) < 0)
		return -1;
	printf("system exit.\n");
	return(status);
}

/*system old*/
int my_system_old(const char *cmdstring){/*version without signal handling*/
	pid_t pid;
	int status;
	
	if(cmdstring==NULL){
		return(1);/*always a command processor with UNIX*/
	}

	if((pid=fork())<0){
		status = -1;/*probably out of processes*/
	}else if(pid==0){/*child process*/
		execl("/bin/bash", "bash", "-c", cmdstring, NULL);
		_exit(127);/*execl error*/
	}else{/*parent*/
		while(waitpid(pid, &status, 0) < 0){
			if(errno!=EINTR){
				status = -1;/*error other than EINTR from waitpid()*/
				break;
			}
		}
	}
	return(status);
}

