/*
 * =====================================================================================
 *
 *       Filename:  04_hello.c
 *
 *    Description:  get the current process id.
 *
 *        Version:  1.0
 *        Created:  04/17/13 23:34:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

int main(void){
	printf("hello world from process ID %d\n", getpid());
	exit(0);
}

