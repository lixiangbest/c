/*
 * =====================================================================================
 *
 *       Filename:  t_raw.c
 *
 *    Description:  term raw.
 *
 *        Version:  1.0
 *        Created:  06/21/13 22:42:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

static void sig_catch(int signo){
	printf("signal caught\n");
	tty_reset(STDIN_FILENO);
	exit(0);
}

#ifdef ECHO
int echo = 1;
#else
int echo = 0;
#endif

int main(void){
	int i;
	char c;

	printf("The linux isdef ECHO = %d\n", echo);
	
	if(signal(SIGINT, sig_catch) == SIG_ERR) /*catch signals*/
		err_sys("signal(SIGINT) error");
	if(signal(SIGQUIT, sig_catch) == SIG_ERR)
		err_sys("signal(SIGQUIT) error");
	if(signal(SIGTERM, sig_catch) == SIG_ERR)
		err_sys("signal(SIGTERM) error");

	if(tty_raw(STDIN_FILENO) < 0)
		err_sys("tty_raw error");
	printf("Enter raw mode characters\n terminate with DELETE(backspace)\n");
	while((i = read(STDIN_FILENO, &c, 1)) == 1){
		if((c &= 255) == 0177) /*0177 = ASCII DELETE*/
			break;
		printf("%o\n", c);
	}
	printf("tty_raw end\n");
	if(tty_reset(STDIN_FILENO) < 0)
		err_sys("tty_reset error");
	if(i <= 0)
		err_sys("read error");

	if(tty_cbreak(STDIN_FILENO) < 0)
		err_sys("tty_cbreak error");
	printf("Enter cbreak mode characters, terminate with SIGINT\n");
	while((i = read(STDIN_FILENO, &c, 1)) == 1){
		c &= 255;
		printf("%o\n", c);
	}

	if(tty_reset(STDIN_FILENO) < 0)
		err_sys("tty_reset error");
	if(i <= 0)
		err_sys("read error");
	printf("reset tty!\n");

	exit(0);
}
