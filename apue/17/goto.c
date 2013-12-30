/*
 * =====================================================================================
 *
 *       Filename:  goto.c
 *
 *    Description:  goto sentence usage.
 *
 *        Version:  1.0
 *        Created:  06/16/13 18:01:34
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

int main(void){
	int i = 0;

again:
	i = 1;
	printf("goto again\n");
	sleep(1);

	goto again;
	printf("i = %d\n", i);
	return 0;
}
