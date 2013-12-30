/*
 * =====================================================================================
 *
 *       Filename:  zombie.c
 *
 *    Description:  print zombie process.
 *
 *        Version:  1.0
 *        Created:  05/12/13 00:18:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#ifdef SOLARIS
#define PSCMD "ps -a -o pid,ppid,s,tty,comm"
#else
#define PSCMD "ps -o pid,ppid,state,tty,command"
#endif

int main(void){
	pid_t pid;
	
	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid==0){/*child*/
		exit(0);
	}

	/*parent*/
	sleep(4);
	system(PSCMD);

	if(waitpid(pid,NULL,0) < 0)
		err_sys("wait error");
	exit(0);
}

