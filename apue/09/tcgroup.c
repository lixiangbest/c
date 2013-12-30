/*
 * =====================================================================================
 *
 *       Filename:  tcgroup.c
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
	printf("tcgetpgrp=%d\n",tcgetpgrp(0));
	printf("tcgetsid=%d\n",tcgetsid(0));
	if((pid=fork())<0){
		return 1;
	}else if(pid!=0){/*parent*/
		system("ps -o pid,ppid,pgid,stat,comm");
	}
	return 0;
}

