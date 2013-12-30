/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  test the ptr[-1]
 *
 *        Version:  1.0
 *        Created:  04/24/13 13:54:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<string.h>

int main(void){
	char str[30] = "look this file!";
	char *ptr;
	ptr = str + strlen(str);
	*ptr++ = '/';
	*ptr = 0;//'\0'
	printf("str=%s\n",str);
	printf("ptr=%s\n",ptr-10);
	ptr[-1] = 0;
	printf("str=%s\n",str);
	printf("ptr=%s\n",ptr);
	return 0;
}

