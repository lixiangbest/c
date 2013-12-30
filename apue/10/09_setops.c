/*
 * =====================================================================================
 *
 *       Filename:  09_setops.c
 *
 *    Description:  set options.
 *
 *        Version:  1.0
 *        Created:  05/14/13 13:15:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<signal.h>
#include<errno.h>

/*<signal.h> usually defines NSIG to include signal number 0*/
#define SIGBAD(signo) ((signo) <= 0 || (signo) >= NSIG)

int sigaddset(sigset_t *set, int signo){
	if(SIGBAD(signo)){
		errno = EINVAL;
		return(-1);
	}
	/*set |= 1 << (signo - 1);*//*turn bit on*/
	return 0;
}

int sigdelset(sigset_t *set, int signo){
	if(SIGBAD(signo)){
		errno = EINVAL;
		return -1;
	}
	/**set &= ~(1 << (signo - 1));*//*turn bit off*/
	return 0;
}

int sigismember(const sigset_t *set, int signo){
	if(SIGBAD(signo)){
		errno = EINVAL;
		return -1;
	}
	/*return ((*set & (1 << (signo - 1)))!=0);*/
}

int main(){
	int n = 1;
	int h = 1;
	printf("before move bit:%d\n",n);
	n |= 1<<2;
	printf("after move:%d\n",n);

	printf("before move bit:%d\n",h);
	h &= 1<<2;
	printf("after move:%d\n",h);
}
