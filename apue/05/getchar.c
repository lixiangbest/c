/*
 * =====================================================================================
 *
 *       Filename:  getchar.c
 *
 *    Description:  getchar usage
 *
 *        Version:  1.0
 *        Created:  04/30/13 23:24:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>

int main(void){
	int c;
	while((c=getchar())!=EOF){
		putchar(c);
	}
	printf("c=%d",c);
	return 0;
}

