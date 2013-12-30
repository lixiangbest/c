/*
 * =====================================================================================
 *
 *       Filename:  initsrv2.c
 *
 *    Description:  init server for reuseaddr.
 *
 *        Version:  1.0
 *        Created:  06/12/13 16:04:31
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
	int fd, err;
	int reuse = 1;

	if((fd = socket(addr->sa_family, type, 0)) < 0)
		return -1;
	if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) < 0){
		err = errno;
		goto errout;
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

