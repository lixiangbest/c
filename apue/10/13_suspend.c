/*
 * =====================================================================================
 *
 *       Filename:  13_suspend.c
 *
 *    Description:  suspend usage 2.
 *
 *        Version:  1.0
 *        Created:  05/19/13 09:46:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

volatile sig_atomic_t quitflag;/*set nonzero by signal handler*/

static void sig_int(int signo){/*one signal handler for SIGINT and SIGQUIT*/
	if(signo == SIGINT)
		pr_mask("\ninterrupt: ");
	else if(signo == SIGQUIT){
		pr_mask("\nquit: ");
		quitflag = 1;/*set flag for main loop*/
	}
}

int main(void){
	sigset_t newmask, oldmask, zeromask;
	if(signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal(SIGINT) error");
	if(signal(SIGQUIT, sig_int) == SIG_ERR)
		err_sys("signal(SIGQUIT) error");
	
	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	/*sigaddset(&zeromask, SIGINT);*/

	/*Block SIGQUIT and save current signal mask.*/
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		err_sys("SIG_BLOCK error");
	printf("start quitflag = %d\n", quitflag);
	pr_mask("Before suspend: ");
	/*suspend until receive a signal or interrupt.*/
	/*sleep(5);*/
	while(quitflag == 0){
		sigsuspend(&zeromask);/*change zeromask to newmask,see the results.*/
	}

	pr_mask("After suspend: ");
	
	/*SIGQUIT has been caught and is now blocked; do whatever.*/
	quitflag = 0;

	/*Reset signal mask which unblocks SIGQUIT*/
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
		err_sys("SIG_SETMASK error");
	}

	exit(0);
}

