/*
 * =====================================================================================
 *
 *       Filename:  05_addstdio.c
 *
 *    Description:  add use stdio
 *
 *        Version:  1.0
 *        Created:  06/04/13 23:05:39
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
	int int1, int2;
	char line[MAXLINE];
	
	/*set IO line buf*/
	if(setvbuf(stdin, NULL, _IOLBF, 0) != 0)
		err_sys("setbuf error!");
	if(setvbuf(stdout, NULL, _IOLBF, 0) != 0)
		err_sys("setvbuf error!");

	while(fgets(line, MAXLINE, stdin) != NULL){
		if(sscanf(line, "%d%d", &int1, &int2) == 2){
			if(printf("%d+%d=%d\n", int1, int2, int1+int2) == EOF)
				err_sys("printf error");
		}else{
			if(printf("invalid args\n") == EOF)
				err_sys("printf error");
		}
	}
	exit(0);
}
