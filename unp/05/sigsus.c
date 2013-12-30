/*
 * =====================================================================================
 *
 *       Filename:  sigsus.c
 *
 *    Description:  know the sigsupend.
 *
 *        Version:  1.0
 *        Created:  07/16/13 22:30:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

static void sig_int(int signo){
	printf("\nin sig_int: \n");
	/*kill(getpid(), SIGINT);*/
	return;
}

int main(void){
	sigset_t newmask, oldmask, zeromask;
	if(signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal(SIGINT) error");
	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	
	/*block SIGINT and save current signal mask*/
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		err_sys("SIG_BLOCK error");
	
	/*critical region of code*/
	printf("in critical region:\n");
	
	/*allow all signals and pause*/
	if(sigsuspend(&zeromask) != -1)
		err_sys("sigsuspend error");
	
	printf("after return from sigsuspend:\n");
	/*reset signal mask which unblocks SIGINT*/
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK error");
	
	/*and continue processing...*/
	return 0;
}

