/*
 * =====================================================================================
 *
 *       Filename:  02_fsess.c
 *
 *    Description: fork for a new session.
 *
 *        Version:  1.0
 *        Created:  05/13/13 23:02:09
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

int main(){
	pid_t pid;
	if((pid=fork())<0){
		err_sys("fork error");
	}else if(pid==0){/*child process*/
		setsid();
		system("ps -o pid,ppid,pgid,session,sid,tty,tpgid,comm");
		exit(0);
	}
	
	if(waitpid(pid,NULL,0)<0){
		err_sys("wait error");
	}
	system("ps -o pid,ppid,pgid,session,sid,tty,tpgid,comm");
	exit(0);
}

