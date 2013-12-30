/*
 * =====================================================================================
 *
 *       Filename:  01_settty.c
 *
 *    Description:  set tty attr.
 *
 *        Version:  1.0
 *        Created:  06/16/13 23:51:56
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

int main(void){
	struct termios term;
	long vdisable;
	int nread;
	char buf[MAXLINE];

	if(isatty(STDIN_FILENO) == 0){
		err_quit("standard input is not a terminal device");
	}

	if((vdisable = fpathconf(STDIN_FILENO, _PC_VDISABLE)) < 0)
		err_quit("fpathconf error or _POSIX_VDISABLE not in effect");
	printf("vdisable:%d\n", vdisable);

	if(tcgetattr(STDIN_FILENO, &term) < 0) /*fetch tty state*/
		err_sys("tcgetattr error");

	term.c_cc[VINTR] = vdisable;/*disable INTR character*/
	term.c_cc[VEOF] = 2;/*EOF is Control-B*/

	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) < 0)
		err_sys("tcsetattr error");

	/*kill(getpid(), SIGINT);*//*catch INTR signal differ from disable*/
	while((nread = read(STDIN_FILENO, buf, MAXLINE)) > 0){
		write(STDOUT_FILENO, buf, nread);
	}
	exit(0);
}
