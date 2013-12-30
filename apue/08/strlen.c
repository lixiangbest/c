/*
 * =====================================================================================
 *
 *       Filename:  strlen.c
 *
 *    Description:  strlen and sizeof
 *
 *        Version:  1.0
 *        Created:  05/08/13 01:26:59
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
#include<string.h>

int main(){
	char *c = "abcdef";
	char d[] = "abcdef";
	char e[] = {'a','b','c','d','e','f'};
	printf("%d %d\n", sizeof(c), strlen(c));
	printf("%d %d\n", sizeof(d), strlen(d));
	printf("%d %d\n", sizeof(e), strlen(e));
	printf("empty=%d\n",printf(""));
}

