/*
 * =====================================================================================
 *
 *       Filename:  async_sock.c
 *
 *    Description:  open on or off async socket.
 *
 *        Version:  1.0
 *        Created:  06/12/13 18:10:56
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
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/ioctl.h>

int setasync(int sockfd){
	int n;
	if(fcntl(sockfd, F_SETOWN, getpid()) < 0)
		return -1;
	n = 1;
	if(ioctl(sockfd, FIOASYNC, &n) < 0)
		return -1;
	return 0;
}

int clrasync(int sockfd){
	int n;
	n = 0;
	if(ioctl(sockfd, FIOASYNC, &n) < 0)
		return -1;
	return 0;
}
