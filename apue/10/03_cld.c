/*
 * =====================================================================================
 *
 *       Filename:  03_cld.c
 *
 *    Description:  signal child
 *
 *        Version:  1.0
 *        Created:  05/14/13 05:33:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<sys/wait.h>

static void sig_cld(int);

int main(){
	pid_t pid;

	if(signal(SIGCLD, sig_cld) == SIG_ERR)
		perror("signal error");
	if((pid=fork())<0){
		perror("fork error");
	}else if(pid==0){/*child*/
		/*first child fork second child.*/
		if((pid=fork())<0){
			perror("fork error");
		}else if(pid==0){/*second child*/
			sleep(4);
			printf("second child get pid = %d, ppid = %d\n", getpid(), getppid());
		}else{/*first child*/
			sleep(2);
			printf("first child get pid = %d, ppid = %d\n", getpid(), getppid());
		}
		_exit(0);
	}else{
		/*parent another fork*/
		if((pid=fork())<0){
			perror("fork error");
		}else if(pid==0){/*child*/
			sleep(1);	
			printf("parent second child get pid = %d, ppid = %d\n", getpid(), getppid());
			_exit(0);
		}
	}
	pause();/*parent is sleep and not wake until catch a signal.*/
	printf("you will see this after waked.\n");
	/*sleep(4);*/
	exit(0);
}

static void sig_cld(int signo){/*interrupts pause()*/
	pid_t pid;
	int status;
	/*
	if(signo==SIGCHLD){
		err_sys("SIGCHLD error\n");
	}
	*/
	printf("SIGCLD received\n");
	if((pid = wait(&status)) < 0){/*fetch child status*/
		perror("wait error");
	}
	pr_exit(status);
	printf("status = %d,pid = %d\n", status, pid);
	if(signal(SIGCLD, sig_cld) == SIG_ERR){/*reestablish handler*/
		perror("signal error");
	}
}
