/*
 * =====================================================================================
 *
 *       Filename:  myuclc.c
 *
 *    Description:  my upper case to  lower case.
 *
 *        Version:  1.0
 *        Created:  06/03/13 22:07:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<ctype.h>
#include<signal.h>

static void sig_int(int signo){
	if(signo == SIGINT)
		printf("catch SIGINT\n");
	else
		printf("catch SIGQUIT\n");
}

int main(void){
	char c;

	if(signal(SIGINT, sig_int)){
		err_sys("SIGINT");
	}
	if(signal(SIGQUIT, sig_int)){
		err_sys("SIGQUIT");
	}

	while((c = getchar()) != EOF){
		if(isupper(c))
			c = tolower(c);
		if(putchar(c) == EOF)
			err_sys("output error");
		if(c == '\n')
			fflush(stdout);
	}
	printf("c = %d,%c,0x%x\n", c, c, c);
	/*sleep(2);*/
	exit(0);
}

