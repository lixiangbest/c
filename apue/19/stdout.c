/*
 * =====================================================================================
 *
 *       Filename:  stdout.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/29/13 17:08:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>

int main(){
	char s[5];
	fputs(fgets(s,5,stdin),stdout);
	return 0;
}

