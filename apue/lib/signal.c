/*
 * =====================================================================================
 *
 *       Filename:  signal.c
 *
 *    Description:  my signal complish.
 *
 *        Version:  1.0
 *        Created:  05/18/13 14:14:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

/* Reliable version of signal(), using POSIX sigaction().  */
/* typedef void Sigfunc(int); */
Sigfunc *signal(int signo, Sigfunc *func){
	struct sigaction act, oact;

	act.sa_handler = func;/*sig handler*/
	sigemptyset(&act.sa_mask);/*sig mask*/
	act.sa_flags = 0;
	if(signo == SIGALRM){
		#ifdef SA_INTERRUPT
			act.sa_flags |= SA_INTERRUPT;
		#endif
	}else{
		#ifdef SA_RESTART
			act.sa_flags |= SA_RESTART;
		#endif
	}
	if(sigaction(signo, &act, &oact) < 0)
		return SIG_ERR;
	return(oact.sa_handler);
}
