/*
 * =====================================================================================
 *
 *       Filename:  t_getpass.c
 *
 *    Description:  get password.
 *
 *        Version:  1.0
 *        Created:  06/19/13 03:38:02
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
#include<termios.h>

#define MAX_PASS_LEN 8 /*max #chars for user to enter*/

char *my_getpass(const char *prompt){
	static char buf[MAX_PASS_LEN+1];/*null byte at end*/
	char *ptr;
	sigset_t sig, osig;
	struct termios ts, ots;
	FILE *fp;
	int c;

	if((fp = fopen(ctermid(NULL), "r+")) == NULL)
		return NULL;
	setbuf(fp, NULL);/*set fp buf type*/

	sigemptyset(&sig);
	sigaddset(&sig, SIGINT);/*block SIGINT*/
	sigaddset(&sig, SIGTSTP);/*block SIGTSTP*/
	sigprocmask(SIG_BLOCK, &sig, &osig);/*and save mask*/

	tcgetattr(fileno(fp), &ts);/*save tty state*/
	ots = ts;/*structure copy*/
	/* 
	 * ~ECHO will forbit the char echo.
	 * ~ECHOK delete the last char in current line.
	 * ~ECHOE delete all chars in current line.
	 * ~ECHONL delete the NL(next line).
	 */
	ts.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
	tcsetattr(fileno(fp), TCSAFLUSH, &ts);
	fputs(prompt, fp);

	ptr = buf;
	while((c = getc(fp)) != EOF && c != '\n')
		if(ptr < &buf[MAX_PASS_LEN])
			*ptr++ = c;
	*ptr = 0;/*null terminate*/
	putc('\n', fp);/*we echo a newline*/

	tcsetattr(fileno(fp), TCSAFLUSH, &ots);/*restore TTY state*/
	sigprocmask(SIG_SETMASK, &osig, NULL);/*restore mask*/
	fclose(fp);/*done with /dev/tty*/
	return buf;
}

int main(){
	char *ptr;

	printf("ctermid = %s\n", ctermid(NULL));
	if((ptr = my_getpass("Enter password:")) == NULL)
		err_sys("getpass error");
	printf("password: %s\n", ptr);

	/*now use password (probably encrypt it) ...*/
	while(*ptr != 0)
		*ptr++ = 0;/*zero it out when we're done with it*/
	exit(0);
}
