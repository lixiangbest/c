/*
 * =====================================================================================
 *
 *       Filename:  02_echoarg.c
 *
 *    Description:  echo arg
 *
 *        Version:  1.0
 *        Created:  05/05/13 21:50:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

int main(int argc, char *argv[]){
	int i;
	/*echo all command-line args*/
	for(i=0;i<argc;i++){
		printf("argv[%d]: %s\n", i, argv[i]);
	}
	printf("argv[%d]=%d,%s\n",i,(int)argv[i],argv[i]);
	/*extern char **environ*/
	printf("getenv HOME: %s; SHELL: %s\n",getenv("HOME"),getenv("SHELL"));
	while(*environ){
		printf("get environ:%s\n",*environ);
		environ++;
	}
	putenv("SHELL=/bin/sh");
	printf("after putenv, getenv SHELL: %s\n",getenv("SHELL"));
	setenv("SHELL","/bin/bash",1);
	printf("after setenv, getenv SHELL: %s\n",getenv("SHELL"));
	unsetenv("SHELL");
	printf("after unsetenv, getenv SHELL: %s\n",getenv("SHELL"));
	exit(0);
}

