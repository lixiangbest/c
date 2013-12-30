/*
 * =====================================================================================
 *
 *       Filename:  twait.c
 *
 *    Description:  tell wait.
 *
 *        Version:  1.0
 *        Created:  05/19/13 23:26:27
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
	int count = 0;
	TELL_WAIT();

	printf("in parent process\n");
	count++;
	printf("count = %d\n", count);
	if((pid=fork()) < 0){
		err_sys("fork error");
	}else if(pid==0){
		printf("in child process\n");
		count++;
		printf("count=%d\n", count);
		TELL_PARENT(getppid());/*parent send blocking SIGUSR2*/
		while(1){
			sleep(2);
			TELL_WAIT();/*block SIGUSR1 and SIGUSR2*/
			WAIT_PARENT();/*let parent run*/
			count = count+2;
			printf("in child process\n");
			printf("count=%d\n",count);
			TELL_PARENT(getppid());
		}
		exit(0);
	}
	sleep(2);
	while(1){
		sleep(2);
		TELL_WAIT();
		WAIT_CHILD();/*parent wait for child send kill -USR2*/
		count = count+2;
		printf("in parent process\n");
		printf("count = %d\n",count);
		TELL_CHILD(pid);/*send child kill -USR1*/
	}
	exit(0);
}

