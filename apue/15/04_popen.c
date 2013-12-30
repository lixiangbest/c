/*
 * =====================================================================================
 *
 *       Filename:  04_popen.c
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
	if((fpin = popen("./myuclc", "r")) == NULL)
		err_sys("popen error");
	
	for(;;){
		fputs("prompt > ", stdout);
		fflush(stdout);
		/*read from pipe*/
		if(fgets(line, MAXLINE, fpin) == NULL){
			perror("fgets");
			break;
		}
		if(fputs(line, stdout) == EOF)
			err_sys("fputs error to pipe");
	}
	if(pclose(fpin) == -1)
		err_sys("pclose error");
	putchar('\n');
	exit(0);
}

