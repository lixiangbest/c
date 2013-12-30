/*
 * =====================================================================================
 *
 *       Filename:  select.c
 *
 *    Description:  select I/O
 *
 *        Version:  1.0
 *        Created:  06/29/13 17:55:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<sys/types.h>
#include<errno.h>
#include<sys/time.h>

int input_timeout(int filedes, unsigned int seconds){
	fd_set set;
	struct timeval timeout;

	/*Initialize the file descriptor set*/
	FD_ZERO(&set);
	FD_SET(filedes, &set);

	/*Initialize the timeout data structure.*/
	timeout.tv_sec = seconds;
	timeout.tv_usec = 0;

	/*select returns 0 if timeout, 1 if input available,-1 if error.*/
	return TEMP_FAILURE_RETRY(select(FD_SETSIZE, &set, NULL, NULL, &timeout));
}

int main(void){
	printf("FD_SETSIZE:0x%x\n", FD_SETSIZE);
	fprintf(stderr, "select returned %d.\n", input_timeout(STDIN_FILENO, 5));
	return 0;
}

