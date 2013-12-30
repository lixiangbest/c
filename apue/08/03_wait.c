/*
 * =====================================================================================
 *
 *       Filename:  03_wait.c
 *
 *    Description:  wait
 *
 *        Version:  1.0
 *        Created:  05/08/13 03:48:36
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
	int status;
	if((pid=fork())<0){
		err_sys("fork error");
	}else if(pid==0){/*child*/
		exit(8);
	}
	
	if(wait(&status) != pid){/*wait for child*/
		err_sys("wait error");
	}
	pr_exit(status);/*and print its status*/

	
	if((pid=fork())<0){
		err_sys("fork error");
	}else if(pid==0){/*child*/
		abort();/*generates SIGABRT*/
	}

	if(wait(&status) != pid){/*wait for child*/
		err_sys("wait error");
	}
	pr_exit(status);/*and print its status*/

	if((pid=fork())<0){
		err_sys("fork error");
	}else if(pid==0){/*child*/
		status /= 0;/*divide by 0 generates SIGFPE*/
	}

	if(wait(&status) != pid){/*wait for child*/
		err_sys("wait error");
	}
	pr_exit(status);/*and print its status*/

	exit(0);
}

