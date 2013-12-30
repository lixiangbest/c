/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  test the fputs
 *
 *        Version:  1.0
 *        Created:  04/20/13 11:16:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char *argv[]){
	printf("stdin=%d,stdout=%d,stderr=%d\n",STDIN_FILENO,STDOUT_FILENO,STDERR_FILENO);
	fputs(argv[0],stdout);
	printf("\n%d",~1);
	exit(0);
}
