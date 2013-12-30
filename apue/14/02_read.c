/*
 * =====================================================================================
 *
 *       Filename:  02_read.c
 *
 *    Description:  read a file
 *
 *        Version:  1.0
 *        Created:  05/27/13 22:57:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include <fcntl.h>

int main(void){
	int fd;
	char buf[2];
	int n;
	fd = open("test.txt",O_RDONLY);
	lseek(fd, 1, SEEK_SET);
	if((n =read(fd, buf, 1))!=1){
		perror("read error");
	}else
		printf("read:%s\n",buf);

	if((n = write(fd, buf, 1)) != 1){
		perror("write error");
	}
	return 0;
}

