/*
 * =====================================================================================
 *
 *       Filename:  03_popen.c
 *
 *    Description:  popen.c
 *
 *        Version:  1.0
 *        Created:  06/02/13 23:08:25
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

#define PAGER "${PAGER:-more}" /*environment variable, or default*/

int main(int argc, char *argv[]){
	char line[MAXLINE];
	FILE *fpin, *fpout;
	int fd;

	if(argc != 2){
		err_quit("usage: a.out <pathname>");
	}
	
	if((fpin = fopen(argv[1], "r")) == NULL){
		err_sys("can't open %s", argv[1]);
	}

	/*pipe open, use our defined popen function.*/
	if((fpout = mypopen(PAGER, "w")) == NULL){
		err_sys("popen error");
	}

	/*copy argv[1] to pager*/
	while(fgets(line, MAXLINE, fpin) != NULL){
		/*output to more cmd.*/
		if(fputs(line, fpout) == EOF)
			err_sys("fputs error to pipe");
	}

	if(ferror(fpin))
		err_sys("fgets error");

	fd = fileno(fpout);
	printf("fileno:%d\n", fd);
	
	/*use our defined pclose function.*/
	if(mypclose(fpout))
		err_sys("pclose error");
	printf("pipe finish\n");
	exit(0);
}
