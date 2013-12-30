/*
 * =====================================================================================
 *
 *       Filename:  02_fgetsfputs.c
 *
 *    Description:  fgets fputs function
 *
 *        Version:  1.0
 *        Created:  04/30/13 16:51:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#define LEN 5

int main(void){
	char buf[LEN];
	while(fgets(buf,LEN, stdin)!=NULL){
		printf("||");
		/*if fputs error, return EOF*/
		if(fputs(buf, stdout) == EOF)
			err_sys("output error");
	}
	/*error or EOF,fgets return NULL. you should consider error.*/
	if(ferror(stdin))
		err_sys("input error");
	exit(0);
}

