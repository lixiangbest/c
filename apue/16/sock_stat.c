/*
 * =====================================================================================
 *
 *       Filename:  sock_stat.c
 *
 *    Description:  sock fd stat
 *
 *        Version:  1.0
 *        Created:  06/12/13 16:52:36
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
#include<sys/socket.h>
#include<sys/stat.h>
#include<unistd.h>

int main(){
	int sock_fd;

	if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		err_sys("create socket error.");
	}

	struct stat sock_stat;
	if(fstat(sock_fd, &sock_stat) < 0){
		err_sys("fstat socket fd.");
	}
	printf("the socket fd is %d\n", sock_fd);
	printf("fstat: sock_stat.st_mode 0%o\n\
sock_stat.st_ino %ld\n\
sock_stat.st_dev %d\n\
sock_stat.st_rdev %d\n\
sock_stat.st_nlink %d\n\
sock_stat.st_uid %d\n\
sock_stat.st_gid %d\n\
sock_stat.st_size %d\n\
sock_stat.st_atime %ld\n\
sock_stat.st_mtime %ld\n\
sock_stat.st_ctime %ld\n\
sock_stat.st_blksize %ld\n\
sock_stat.st_blocks %d\n\
", sock_stat.st_mode, sock_stat.st_ino, sock_stat.st_dev, sock_stat.st_rdev, sock_stat.st_nlink, sock_stat.st_uid, sock_stat.st_gid, sock_stat.st_size, sock_stat.st_atime, sock_stat.st_mtime, sock_stat.st_ctime, sock_stat.st_blksize, sock_stat.st_blocks);
	return 0;
}
