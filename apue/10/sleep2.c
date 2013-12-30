/*
 * =====================================================================================
 *
 *       Filename:  sleep2.c
 *
 *    Description:  old sleep complish
 *
 *        Version:  1.0
 *        Created:  05/14/13 10:32:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<setjmp.h>
#include<signal.h>
#include<unistd.h>
#include<stdio.h>

static jmp_buf env_alrm;

static void sig_alrm(int signo){
	printf("long jump in sig_alrm.\n");
	longjmp(env_alrm, 1);
}

unsigned int sleep2(unsigned int nsecs){
	if(signal(SIGALRM, sig_alrm)==SIG_ERR){
		return(nsecs);
	}
	if(setjmp(env_alrm) == 0){
		alarm(nsecs);/*start the timer*/
		pause();/*next caught signal wakes us up*/
	}
	return(alarm(0));/*turn off timer, return unslept time*/
}
