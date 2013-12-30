/*
 * =====================================================================================
 *
 *       Filename:  signal.c
 *
 *    Description:  sigsuspend
 *
 *        Version:  1.0
 *        Created:  05/26/13 17:59:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

static void sig_usr(int signo){
	if(signo == SIGUSR1){
		printf("catch SIGUSR1.");
	}else if(signo == SIGHUP){
		printf("catch SIGHUP.");
	}
}

int main(){
	struct sigaction sa;
	sigset_t waitmask;
	if(signal(SIGUSR1, sig_usr) < 0){
		err_sys("err signal.");
	}
	if(signal(SIGHUP, sig_usr) < 0){
		err_sys("err signal.");
	}
	
	/*ignore SIG_IGN*/
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if(sigaction(SIGHUP, &sa, NULL) < 0){
		err_quit("%s: can't ignore SIGHUP");
	}

	/*suspend, find if ignore the SIGHUP.*/
	sigemptyset(&waitmask);
	if(sigsuspend(&waitmask) != -1){
		err_sys("sigsuspend error");
	}
	printf("after suspend.");
	return 0;
}

