/*
 * =====================================================================================
 *
 *       Filename:  siglist.c
 *
 *    Description:  siglist function usage.
 *
 *        Version:  1.0
 *        Created:  05/19/13 21:31:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<signal.h>

int main(void){
	printf("sys_siglist=%s\n",sys_siglist[2]);
	printf("strsiglist=%s\n",strsignal(SIGTSTP));
	return 0;
}

