/*
 * =====================================================================================
 *
 *       Filename:  03_mycat.c
 *
 *    Description:  my cat
 *
 *        Version:  1.0
 *        Created:  04/20/13 21:03:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

#define BUFFSIZE 4096

int main(void){
	int n;
	char buf[BUFFSIZE];

	while((n=read(STDIN_FILENO, buf, BUFFSIZE))>0){
		printf("\nn=%d\n",n);
		if(write(STDOUT_FILENO, buf, n) != n){
			err_sys("write error");
		}
	}
	if( n < 0)
		err_sys("read error");
	exit(0);
}
