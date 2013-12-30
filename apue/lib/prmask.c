/*
 * =====================================================================================
 *
 *       Filename:  promask.c
 *
 *    Description:  print the signal mask
 *
 *        Version:  1.0
 *        Created:  05/14/13 15:12:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include <errno.h>

void pr_mask(const char *str){
	sigset_t sigset;
	int errno_save;

	errno_save = errno;/*we can be called by signal handlers*/
	if(sigprocmask(0, NULL, &sigset) < 0)
		err_sys("sigprocmask error");

	printf("%s", str);
	
	if(sigismember(&sigset, SIGINT))
		printf("SIGINT ");
	if(sigismember(&sigset, SIGQUIT))
		printf("SIGQUIT ");
	if(sigismember(&sigset, SIGUSR1))
		printf("SIGUSR1 ");
	if(sigismember(&sigset, SIGALRM))
		printf("SIGALRM ");

	/* remaining signals can go there */
	printf("\n");
	errno = errno_save;
}

