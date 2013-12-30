/*
 * =====================================================================================
 *
 *       Filename:  winch.c
 *
 *    Description:  window size change.
 *
 *        Version:  1.0
 *        Created:  06/22/13 11:44:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<termios.h>
#ifndef TIOCGWINSZ
#include<sys/ioctl.h>
#endif

static void pr_winsize(int fd){
	struct winsize size;

	if(ioctl(fd, TIOCGWINSZ, (char *)&size) < 0)
		err_sys("TIOCGWINSZ error");
	printf("%d rows, %d columns\n", size.ws_row, size.ws_col);
}

static void sig_winch(int signo){
	printf("SIGWINCH received\n");
	pr_winsize(STDIN_FILENO);
}

int main(void){
	if(isatty(STDIN_FILENO) == 0)
		exit(1);
	if(signal(SIGWINCH, sig_winch) == SIG_ERR)
		err_sys("signal error");
	pr_winsize(STDIN_FILENO);/*print initial size*/
	for(;;) /*and sleep forever*/
		pause();
	printf("after pause()\n");

	return 0;
}
