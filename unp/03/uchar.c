/*
 * =====================================================================================
 *
 *       Filename:  uchar.c
 *
 *    Description:  unsigned char and char
 *
 *        Version:  1.0
 *        Created:  07/13/13 17:14:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

void f(unsigned char v){
	char c = v;/*-128~127*/
	unsigned char uc = v;/*0~255*/
	unsigned int a = c, b = uc;
	int i = c, j = uc;
	printf("--------------\n");
	printf("u char 0x%x\n", v);
	printf("%%c: %c, %c\n", c, uc);
	printf("%%X: %X, %X\n", c, uc);
	printf("%%u: %u, %u\n", a, b);
	printf("%%d: %d, %d\n", i, j);
}

char *sta_char(){
	static char str[128] = "static test";
	return str;
}

int main(int argc, char *argv[]){
	printf("ifdef IPV6:%d\n", IPV6);
	printf("static char in function: %s\n", sta_char());
	f(0x80);/*128*/
	f(0x7f);/*127*/
	return 0;
}
