/*
 * =====================================================================================
 *
 *       Filename:  07_read.c
 *
 *    Description:  07 read
 *
 *        Version:  1.0
 *        Created:  05/14/13 12:02:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

Sigfunc *signal_intr(int,Sigfunc*);
static void sig_alrm(int);

int main(void){
	int n;
	char line[MAXLINE];
	/* signal mofify signal_intr our defined function.
	 * avoid the system call restart.
	 */
	if(signal_intr(SIGALRM, sig_alrm) == SIG_ERR){
		err_sys("signal(SIGALRM) error");
	}
	printf("alarm time: %d\n", alarm(5));
	if((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
		err_sys("read error");
	printf("alarm time: %d\n", alarm(0));

	write(STDOUT_FILENO, line, n);
	exit(0);
}

static void sig_alrm(int signo){
	/*nothing to do, just return to interrupt the read*/
}
