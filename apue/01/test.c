/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  test the #define
 *
 *        Version:  1.0
 *        Created:  10/19/12 21:53:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#ifndef _APUE_H
#define _APUE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h> //for definition of errno
#include<stdarg.h> //ISO C variable arguments.

void err_quit(const char*,...);
void err_sys(const char*,...);

#endif /*_APUE_H*/

int main(int argc,char *argv[]){
	printf("Test the _APUE_H\n");
	//err_quit("usage: ls directory_name");
	err_sys("can't open %s",argv[1]);
	exit(0);
}

/*
 * Print a message and return to caller.
 * Caller specifies "errnoflag"
 */
static void err_doit(int errnoflag,int error,const char*fmt,va_list ap){
	char buf[80];
	vsnprintf(buf,80,fmt,ap);
	printf("%d\n",errno);
	if(errnoflag){
		snprintf(buf+strlen(buf),80-strlen(buf),": %s",strerror(error));
	}
	strcat(buf,"\n");
	fflush(stdout);/*in case stdout and stderr are the same*/
	fputs(buf,stderr);
	fflush(NULL);/*flushes all stdio output streams*/
}

/*
 * Nonfatal error unrelated to a system call.
 * Print a message and return.
 */
void err_quit(const char *fmt,... ){
	va_list ap;
	va_start(ap,fmt);
	err_doit(0,0,fmt,ap);
	va_end(ap);
	exit(1);
}

/*
 * Fatal error related to a system call.
 * Print a message and terminate.
 */
void err_sys(const char*fmt,...){
	va_list ap;
	va_start(ap,fmt);
	err_doit(1,errno,fmt,ap);
	va_end(ap);
	exit(1);
}

