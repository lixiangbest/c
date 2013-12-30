/*
 * =====================================================================================
 *
 *       Filename:  systest1.c
 *
 *    Description:  my system function test.
 *
 *        Version:  1.0
 *        Created:  05/11/13 17:11:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<sys/wait.h>

int main(void){
	int status;
	if((status = system("date")) < 0)
		err_sys("system() error");
	pr_exit(status);
	printf("\n");

	if((status = system("nosuchcommand")) < 0){
		err_sys("system() error");
	}
	pr_exit(status);
	printf("\n");

	if((status = system("who; exit -1")) < 0){
		err_sys("system() error");
	}
	pr_exit(status);

	exit(0);
}

