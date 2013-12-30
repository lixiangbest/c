/*
 * =====================================================================================
 *
 *       Filename:  echoall.c
 *
 *    Description:  echoall
 *
 *        Version:  1.0
 *        Created:  05/11/13 11:00:05
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
	char **ptr;
	extern char **environ;

	for(i=0;i<argc;i++){/*echo all command-line args*/
		printf("argv[%d]:%s\n", i, argv[i]);
	}

	for(ptr=environ;*ptr!=0;ptr++){/*and all env strings*/
		printf("%s\n", *ptr);
	}

	exit(0);
}

