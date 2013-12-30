/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  test the unsigned char
 *
 *        Version:  1.0
 *        Created:  04/30/13 14:46:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>

int s(int (*m)(FILE *fp)){
	/*printf("fgetc=%c\n",(*m)(stdin));*/
	putc((*m)(stdin), stdout);
}

int main(void){
	char c = -1;
	printf("c=%c,c=%d\n",c,c);
	s(fgetc);
	return 0;
}

