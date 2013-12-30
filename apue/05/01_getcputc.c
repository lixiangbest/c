/*
 * =====================================================================================
 *
 *       Filename:  01_getcputc.c
 *
 *    Description:  getc putc function
 *
 *        Version:  1.0
 *        Created:  04/30/13 16:30:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

int main(void){
	int c;
	while((c = getc(stdin)) != EOF)
		if(putc(c, stdout) == EOF)
			err_sys("output error!");
	if(ferror(stdin))
		err_sys("input error");
	exit(0);
}

