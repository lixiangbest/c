/*
 * =====================================================================================
 *
 *       Filename:  08_read.c
 *
 *    Description:  08 read
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
#include<setjmp.h>

static void sig_alrm(int);
static jmp_buf env_alrm;

int main(void){
	int n;
	char line[MAXLINE];

	if(signal(SIGALRM, sig_alrm) == SIG_ERR){
		err_sys("signal(SIGALRM) error");
	}
	/*if jump.*/
	if(setjmp(env_alrm) != 0){
		err_quit("read timeout");
	}

	printf("alarm time: %d\n", alarm(10));
	if((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
		err_sys("read error");
	printf("alarm time: %d\n", alarm(0));

	write(STDOUT_FILENO, line, n);
	exit(0);
}

static void sig_alrm(int signo){
	printf("set long jump in sig_alrm.\n");
	longjmp(env_alrm, 1);
}
