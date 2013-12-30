/*
 * =====================================================================================
 *
 *       Filename:  07_exec.c
 *
 *    Description:  exec function list.
 *
 *        Version:  1.0
 *        Created:  05/11/13 10:15:31
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

char *env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main(void){
	pid_t pid;
	printf("uid=%d,euid=%d\n",getuid(),geteuid());
	printf("_SC_SAVED_IDS=%ld\n",sysconf(_SC_SAVED_IDS));
	if((pid=fork())<0){
		err_sys("fork error");
	}else if(pid==0){
		/*child process, specify pathname, specify environment*/
		if(execle("/home/suncco/c/apue/08/echoall", "echo", "myarg1", "MY ARG2", (char*)0, env_init)<0)
			err_sys("execle error");
	}

	/*parent process*/
	if(waitpid(pid, NULL, 0)<0){
		err_sys("wait error");
	}
	
	putenv("PATH=/home/suncco/c/apue/08");
	if((pid=fork())<0){
		err_sys("fork error");
	}else if(pid==0){/*specify filename, inherit environment*/
		if(execlp("echoall", "echoall", "only 1 arg", (char*)0)<0)
			err_sys("execlp error");
	}

	/*parent process*/
	/*
	if(waitpid(pid, NULL, 0)<0){
		err_sys("wait error");
	}
	*/

	exit(0);
}

