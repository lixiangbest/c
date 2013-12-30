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

int lockfile(int fd){
	struct flock fl;
	
	fl.l_type = F_WRLCK;
	fl.l_start = 0;
	fl.l_whence = SEEK_SET;
	fl.l_len = 0;
	return(fcntl(fd, F_SETLKW, &fl));
}

int main(void){
	int fd,n;
	pid_t pid;
	char buf[3];

	/*open file in write-read.*/
	if((fd = open("templock", O_RDWR|O_CREAT)) < 0){
		err_sys("open error");
	}
	/*lseek(fd, 1, SEEK_SET);*/

	if(write_lock(fd, 0, SEEK_SET, 2) < 0){/*add write lock*/
		err_sys("write error");
	}

	/*
	if(lockfile(fd) < 0){
		err_sys("lock the whole file error");
	}
	*/

	if((n = read(fd, buf, 2)) < 0){
		err_sys("read error");
	}else{
		write(STDOUT_FILENO, buf, n);
	}

	read_lock(fd, 1, SEEK_CUR, 3);
	getchar();
	write_lock(fd, 1, SEEK_CUR, 3);
	getchar();
	exit(0);
}
