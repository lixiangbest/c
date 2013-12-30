/*
 * =====================================================================================
 *
 *       Filename:  10_critical.c
 *
 *    Description:  signal set and sigprocmask example.
 *
 *        Version:  1.0
 *        Created:  05/18/13 09:54:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

static void sig_quit(int);

int main(void){
	/*char buf[MAXLINE];*/
	sigset_t newmask, oldmask, pendmask;

	if(signal(SIGQUIT, sig_quit) == SIG_ERR)
		err_sys("can't catch SIGQUIT");

	/*
	 * Block SIGQUIT and save current signal mask.
	 */
	/*sigfillset(&newmask);sleep(5);exit(0);*/
	sigemptyset(&newmask);
	/*sleep(5);exit(0);*/
	sigaddset(&newmask, SIGQUIT);
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		err_sys("SIG_BLOCK error");
	/*pr_mask("mask print");exit(0);*/

	sleep(5);/*SIGQUIT here will remain pending*/
	
	/*get the current pending signals.*/
	if(sigpending(&pendmask) < 0){
		err_sys("sigpending error");
	}
	/*check SIGQUIT pending signal in the signal member.*/
	if(sigismember(&pendmask, SIGQUIT)){
		printf("\nSIGQUIT pending\n");
	}

	/*
	 * Reset signal mask which unblocks SIGQUIT
	 */
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK error.");
	printf("SIGQUIT unblocked\n");
	
	sleep(5);/*SIGQUIT here will terminate with core file*/
	printf("SA_INTERRUPT:%o\n", SA_INTERRUPT);
	exit(0);
}

static void sig_quit(int signo){
	printf("caught SIGQUIT\n");
	if(signal(SIGQUIT, SIG_DFL) == SIG_ERR){
		err_sys("can't reset SIGQUIT");
	}
}

