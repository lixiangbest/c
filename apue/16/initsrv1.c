/*
 * =====================================================================================
 *
 *       Filename:  initsrv1.c
 *
 *    Description:  init server.
 *
 *        Version:  1.0
 *        Created:  06/11/13 09:37:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<errno.h>
#include<sys/socket.h>

int initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen){
	int fd;
	int err = 0;

	if((fd = socket(addr->sa_family, type, 0)) < 0){
		return -1;
	}
	if(bind(fd, addr, alen) < 0){
		err = errno;
		goto errout;
	}
	if(type == SOCK_STREAM || type == SOCK_SEQPACKET){
		if(listen(fd, qlen) < 0){
			err = errno;
			goto errout;
		}
	}
	return fd;
errout:
	close(fd);
	errno = err;
	return -1;
}

