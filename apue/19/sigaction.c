/*
 * =====================================================================================
 *
 *       Filename:  sigaction.c
 *
 *    Description:  sigaction usage.
 *
 *        Version:  1.0
 *        Created:  06/29/13 16:10:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<stdio.h>
#include<signal.h>

void handle(int sig){
	if(sig == SIGUSR1)
		printf("catch SIGUSR1\n");
	else if(sig == SIGUSR2)
		printf("catch SIGUSR2\n");
	else if(sig == SIGQUIT)
		printf("catch SIGQUIT\n");
	else if(sig == SIGINT)
		printf("catch SIGINT\n");
}

int main(){
	struct sigaction sa;
	sa.sa_handler = handle;/*The handler function*/
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);

	if(sigaction(SIGINT, &sa, NULL) < 0)
		err_sys("sigaction error");

	if(signal(SIGUSR1, handle) < 0)
		err_sys("signal error");

	while(1){
		printf("Fish.\n");
		sleep(1);
	}
	kill(getpid(), SIGUSR1);

	return 0;
}
