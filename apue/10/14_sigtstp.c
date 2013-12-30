/*
 * =====================================================================================
 *
 *       Filename:  14_sigtstp.c
 *
 *    Description:  signal tstp
 *
 *        Version:  1.0
 *        Created:  05/19/13 21:01:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#define BUFFSIZE 1024

static void sig_tstp(int);

int main(void){
	int n;
	char buf[BUFFSIZE];

	/*only catch SIGTSTP if we're running with a job-controll shell.*/
	if(signal(SIGTSTP, SIG_IGN) == SIG_DFL){
		printf("SIG_DFL\n");
		signal(SIGTSTP, sig_tstp);
	}

	while((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0){
		if(write(STDOUT_FILENO, buf, n) != n)
			err_sys("write error");
	}
	if(n < 0)
		err_sys("read error");
	exit(0);
}

static void sig_tstp(int signo){/*signal handler for SIGTSTP*/
	sigset_t mask;
	/*... move cursor to lower left corner, reset tty mode ...*/

	/*unblock SIGTSTP, since it's blocked while we're handling it.*/
	sigemptyset(&mask);
	sigaddset(&mask, SIGTSTP);
	sigprocmask(SIG_UNBLOCK, &mask, NULL);

	signal(SIGTSTP, SIG_DFL);/*reset disposition to default*/
	
	kill(getpid(), SIGTSTP);/*and send the signal to ourself*/
	/*we won't return from the kill until we're continued*/

	signal(SIGTSTP, sig_tstp);/*reestablish signal handler*/

	/*...reset tty mode, redraw screen...*/
}

