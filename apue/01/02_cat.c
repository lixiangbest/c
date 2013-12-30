/*
 * =====================================================================================
 *
 *       Filename:  02_cat.c
 *
 *    Description:  my cat program
 *
 *        Version:  1.0
 *        Created:  04/16/13 05:22:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */

#include "apue.h"

/*#define BUFFSIZE 4096*/
#define BUFFSIZE 500

int main(void){
	int n;
	char buf[BUFFSIZE];
	while((n=read(STDIN_FILENO, buf, BUFFSIZE))>0){
		printf("n=%d\n",n);
		if(write(STDOUT_FILENO, buf, n)!=n)
			err_sys("write error!");
	}
	if(n<0)
		err_sys("read error!");
	exit(0);
}
