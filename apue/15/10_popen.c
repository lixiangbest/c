/*
 * =====================================================================================
 *
 *       Filename:  10_popen.c
 *
 *    Description:  popen
 *
 *        Version:  1.0
 *        Created:  06/03/13 22:42:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<sys/wait.h>

int main(void){
	char line[MAXLINE];
	FILE *fpin;

	printf("STDIN_FILENO = %d\n", STDIN_FILENO);
	if((fpin = popen("ls m 2>&1", "r")) == NULL)
		err_sys("popen error");

	printf("fileno = %d\n", fileno(fpin));
	/*read from pipe*/
	if(fgets(line, MAXLINE, fpin) == NULL){
		perror("fgets");
	}
	if(fputs(line, stdout) == EOF)
		err_sys("fputs error to pipe");

	if(pclose(fpin) == -1)
		err_sys("pclose error");
	exit(0);
}
