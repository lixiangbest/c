/*
 * =====================================================================================
 *
 *       Filename:  core.c
 *
 *    Description:  core dump generate.
 *
 *        Version:  1.0
 *        Created:  06/23/13 18:01:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>

static void sub(void){
	int *p = NULL;
	printf("%d\n", *p);
}

int main(){
	sub();
	return 0;
}
