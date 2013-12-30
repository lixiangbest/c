/*
 * =====================================================================================
 *
 *       Filename:  lock.c
 *
 *    Description:  my lock
 *
 *        Version:  1.0
 *        Created:  05/28/13 02:14:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<fcntl.h>

int main(void){
	int fd,n;
	pid_t pid;
	char buf[1] = {'a'};
	char rbuf[1];

	/*open file in write-read.*/
	if((fd = open("mylock", O_RDWR|O_CREAT)) < 0){
		err_sys("open error");
	}

	if(write_lock(fd, 0, SEEK_END, 0) < 0){/*add write lock*/
		err_sys("write lock error");
	}

	if(write(fd, buf, 1) != 1){
		err_sys("write error 1");
	}else{
		read(fd, rbuf, 1);
		write(STDOUT_FILENO, rbuf, 1);
	}

	un_lock(fd, 0, SEEK_END, 0);

	if((n = write(fd, buf, 1)) != 1){
		err_sys("write error 2");
	}

	exit(0);
}
