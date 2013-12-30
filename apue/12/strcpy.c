/*
 * =====================================================================================
 *
 *       Filename:  strcpy.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/25/13 00:01:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<string.h>
#include<stdio.h>

int main(void){
	char *str = "lixiang";
	char str1[5];
	strncpy(str1,str,3);
	printf("str1=%s\n", str1);
	
	strcpy(str1, &str[3]);
	printf("str1=%s\n", str1);
	return 0;
}

