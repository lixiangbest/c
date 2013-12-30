/*
 * =====================================================================================
 *
 *       Filename:  pgroup.c
 *
 *    Description:  process group.
 *
 *        Version:  1.0
 *        Created:  05/12/13 17:19:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<sys/wait.h>

int main(){
	pid_t pid;
	printf("Before set group pid,parent pid=%d,process id=%d,process group id=%d,pgid=%d\n",getppid(),getpid(),getpgrp(),getpgid(getpid()));
	if((pid=fork())<0){
		return 1;
	}else if(pid==0){/*child process*/
		printf("Before set group pid,parent = %d,child process id=%d,process group id=%d\n",getppid(),getpid(),getpgrp());
		setpgid(getpid(),getpid());
		printf("After set group pid,parent = %d,child process id=%d,process group id=%d\n",getppid(),getpid(),getpgrp());
		printf("setsid=%d\n",setsid());/*set session id*/
		/*return 0;*/
	}
	if(waitpid(pid,NULL,0)<0){/*parent and child will run.*/
		perror("wait error.");
		return 1;
	}
	printf("After set group pid,process id=%d,process group id=%d,pgid=%d\n",getpid(),getpgrp(),getpgid(getpid()));
	printf("getsid=%d,setsid=%d\n",getsid(getpid()),setsid());/*set session id*/
	return 0;
}

