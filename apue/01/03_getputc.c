/*
 * =====================================================================================
 *
 *       Filename:  03_getputc.c
 *
 *    Description:  use stdio with buffer to get or put char.
 *
 *        Version:  1.0
 *        Created:  04/17/13 22:45:06
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
	while((c=getc(stdin))!=EOF){
		if(putc(c,stdout)==EOF)
			err_sys("output error");
	}
	/*int ferror(FILE *stream),>0 make mistakes.*/
	if(ferror(stdin)){
		err_sys("input error");
	}

	exit(0);
}
