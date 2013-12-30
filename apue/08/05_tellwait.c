/*
 * =====================================================================================
 *
 *       Filename:  05_tellwait.c
 *
 *    Description:  tell wait
 *
 *        Version:  1.0
 *        Created:  05/08/13 06:46:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

static void char_at_a_time(char*);

int main(void){
	pid_t pid;
	if((pid=fork())<0){
		err_sys("fork error");
	}else if(pid==0){/*child*/
		char_at_a_time("output from child\n");
	}else{/*parent*/
		/*sleep(2);*/
		char_at_a_time("output from parent\n");
	}
	exit(0);
}

static void char_at_a_time(char *str){
	char *ptr;
	int c;
	setbuf(stdout, NULL);/*set unbuffered*/
	for(ptr=str;(c=*ptr++)!=0;)
		putc(c, stdout);
}
