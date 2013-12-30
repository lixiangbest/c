/*
 * =====================================================================================
 *
 *       Filename:  12_suspend.c
 *
 *    Description:  suspend critical region of code.
 *
 *        Version:  1.0
 *        Created:  05/18/13 22:05:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<errno.h>

static void sig_int(int);

int main(void){
	sigset_t newmask, oldmask, waitmask;

	pr_mask("program start: ");

	if(signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal(SIGINT) error");
	sigemptyset(&waitmask);
	sigaddset(&waitmask, SIGUSR1);
	pr_mask("After set SIGUSR1: ");
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);
	pr_mask("After set SIGINT: ");
	/*sleep(5);exit(0);*/

	/*Block SIGINT and save current signal mask.*/
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
		err_sys("SIG_BLOCK error");
	}

	/*Critical region of code.*/
	pr_mask("in critical region: ");
	/*sleep(5);exit(0);*/
	/*pause, allowing all signals except SIGUSR1*/
	if(sigsuspend(&waitmask)!=-1)
		err_sys("sigsuspend error");
	else perror("sigsuspend");
	pr_mask("after return from sigsuspend: ");

	/*Reset signal mask which unblocks SIGINT*/
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK error");

	/*And continue processing...*/
	pr_mask("program exit: ");
	exit(0);
}

static void sig_int(int signo){
	pr_mask("\n in sig_int: ");
}

