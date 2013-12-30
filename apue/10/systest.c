/*
 * =====================================================================================
 *
 *       Filename:  systest.c
 *
 *    Description:  system test function
 *
 *        Version:  1.0
 *        Created:  05/19/13 16:10:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<sys/wait.h>

static void sig_int(int signo){
	printf("caught SIGINT\n");
}

static void sig_chld(int signo){
	if(wait(NULL)<0)
		printf("wait error.");
	printf("caught SIGCHLD\n");
}

int my_system(char*);/*my system function.*/

int main(void){
	sigset_t newmask, oldmask;
	if(signal(SIGINT, sig_int) == SIG_ERR){
		err_sys("signal(SIGINT) error");
	}
	if(signal(SIGCHLD, sig_chld) == SIG_ERR){
		err_sys("signal(SIGCHLD) error");
	}
	/*Block the sig_int.*/
	/*
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGINT);
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask)< 0){
		err_sys("SIG_BLOCK error");
	}
	*/
	/*
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL)<0){
		err_sys("SIG_SETMASK error");
	}
	*/
	if(my_system("/bin/ed") < 0)
		err_sys("system() error");
	exit(0);
}

