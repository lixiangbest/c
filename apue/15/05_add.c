/*
 * =====================================================================================
 *
 *       Filename:  05_add.c
 *
 *    Description:  two number add.
 *
 *        Version:  1.0
 *        Created:  06/03/13 23:37:46
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
	int n, int1, int2;
	char line[MAXLINE];

	printf("stdin fileno:%d\n", fileno(stdin));
	while((n = read(STDIN_FILENO, line, MAXLINE)) > 0){
		line[n] = 0;/*null terminate*/
		printf("line = %s", line);
		if(sscanf(line, "%d%d", &int1, &int2) == 2){
			sprintf(line, "%d + %d = %d\n", int1, int2, int1 + int2);
			n = strlen(line);
			if(write(STDOUT_FILENO, line, n) != n)
				err_sys("write error");
		}else{
			if(write(STDOUT_FILENO, "invalid args\n", 13) != 13)
				err_sys("write error");
		}
	}
	exit(0);
}

