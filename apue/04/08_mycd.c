/*
 * =====================================================================================
 *
 *       Filename:  08_mycd.c
 *
 *    Description:  create your cd cmd(change direcotry).
 *
 *        Version:  1.0
 *        Created:  04/24/13 15:09:59
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
	if(chdir("/tmp")<0)
		err_sys("chdir failed");
	printf("chdir to /tmp succeeded\n");
	exit(0);
}
