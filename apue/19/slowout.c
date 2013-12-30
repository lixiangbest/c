/*
 * =====================================================================================
 *
 *       Filename:  slowout.c
 *
 *    Description:  slow out.
 *
 *        Version:  1.0
 *        Created:  06/27/13 23:45:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<unistd.h>

int main(){
	char buf[4096];
	fgets(buf, 4096, stdin);
	sleep(10);
	return 0;
}

