/*
 * =====================================================================================
 *
 *       Filename:  sigabrt.c
 *
 *    Description:  abort function default signaction.
 *
 *        Version:  1.0
 *        Created:  05/19/13 15:40:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<signal.h>

static void sig_abrt(int signo){
	if(signo == SIGABRT){
		printf("SIGABRT received.\n");
	}
}

/*check the abort() default action to abort the process.*/
int main(){
	sigset_t newmask,oldmask;
	if(signal(SIGABRT, sig_abrt) == SIG_ERR){
		perror("SIGABRT error");
		exit(0);
	}
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGABRT);
	/*oldmask store the current mask, change to newmask*/
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask)<0){
		perror("sigpromask error");
	}
	abort();
	/*
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		perror("SIG_SETMASK error");
	*/
	printf("after abort\n");
	exit(0);
}

