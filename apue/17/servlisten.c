/*
 * =====================================================================================
 *
 *       Filename:  servlisten.c
 *
 *    Description:  unix server listen
 *
 *        Version:  1.0
 *        Created:  06/13/13 23:47:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<sys/socket.h>
#include<sys/un.h>
#include<errno.h>

#define QLEN 10

/**
 * Create a server end point of a connection.
 * Returns fd if all OK, <0 on error.
 */
int serv_listen(const char *name){
	int fd, len, err, rval;
	struct sockaddr_un un;

	/*create a UNIX domain stream socket*/
	if((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
		return -1;

	unlink(name);/*in case it already exists*/

	/*fill in socket address structure*/
	memset(&un, 0, sizeof(un));
	un.sun_family = AF_UNIX;
	strcpy(un.sun_path, name);
	len = offsetof(struct sockaddr_un, sun_path) + strlen(name);

	/*bind the name to the descriptor*/
	if(bind(fd, (struct sockaddr *)&un, len) < 0){
		rval = -2;
		goto errout;
	}

	if(listen(fd, QLEN) < 0){/*tell kernel we're a server*/
		rval = -3;
		goto errout;
	}
	return fd;

errout:
	err = errno;
	close(fd);
	errno = err;
	return rval;
}
