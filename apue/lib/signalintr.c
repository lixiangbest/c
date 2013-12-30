/*
 * =====================================================================================
 *
 *       Filename:  signalintr.c
 *
 *    Description:  signal interrupt.
 *
 *        Version:  1.0
 *        Created:  05/18/13 15:00:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

Sigfunc *signal_intr(int signo, Sigfunc *func){
	struct sigaction act, oact;

	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	#ifdef SA_INTERRUPT
	act.sa_flags |= SA_INTERRUPT;
	#endif
	if(sigaction(signo, &act, &oact) < 0)
		return(SIG_ERR);
	return(oact.sa_handler);
}

