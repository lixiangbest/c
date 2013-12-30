/*
 * =====================================================================================
 *
 *       Filename:  segfault1.c
 *
 *    Description:  segmentation fault example.
 *
 *        Version:  1.0
 *        Created:  06/30/13 16:05:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void handle(int signo){
	printf("catch SIGSEGV\n");
	exit(0);
}

int  main(){
	int *ptr = NULL;

	signal(SIGSEGV, handle);

	*ptr = 0;

	return 0;
}

