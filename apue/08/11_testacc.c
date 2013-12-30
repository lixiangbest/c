/*
 * =====================================================================================
 *
 *       Filename:  11_testacc.c
 *
 *    Description:  test account.
 *
 *        Version:  1.0
 *        Created:  05/11/13 18:41:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

int main(void){
	pid_t pid;

	if((pid=fork())<0)
		err_sys("fork error");
	else if(pid!=0){/*parent*/
		sleep(2);
		exit(2);/*terminate with exit status 2*/
	}
	
	/*first child*/
	if((pid=fork())<0){
		err_sys("fork error");
	}else if(pid!=0){
		sleep(4);
		abort();/*terminate with core dump*/
	}
	
	/*second child*/
	if((pid=fork()) < 0){
		err_sys("fork error");
	}else if(pid!=0){
		execl("/bin/dd","dd","if=/home/suncco/c/apue/08/termcap","of=/dev/null",NULL);
		exit(7);/*shouldn't get here*/
	}

	/*third child*/
	if((pid=fork())<0){
		err_sys("fork error");
	}else if(pid!=0){
		sleep(8);
		exit(0);/*normal exit*/
	}

	/*fourth child*/
	sleep(6);
	kill(getpid(), SIGKILL);/*terminate w/signal, no core dump*/
	exit(6);/*shouldn't get here*/
}

