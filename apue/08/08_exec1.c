/*
 * =====================================================================================
 *
 *       Filename:  08_exec1.c
 *
 *    Description:  exec function.
 *
 *        Version:  1.0
 *        Created:  05/11/13 15:54:21
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

int main(void){
	pid_t pid;
	putenv("PATH=/home/suncco/c/apue/08");
	if((pid=fork()) < 0){
		err_sys("fork error");
	}else if(pid==0){/*child*/
		if(execlp("testinterp","testinterp","myarg1","MY ARG2", (char *)0) < 0)
			err_sys("execl error");
	}
	if(waitpid(pid, NULL, 0) < 0){/*parent*/
		err_sys("waitpid error");
	}
	exit(0);
}

