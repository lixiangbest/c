/*
 * =====================================================================================
 *
 *       Filename:  spipe.c
 *
 *    Description:  unix domain socket pipe.
 *
 *        Version:  1.0
 *        Created:  06/15/13 16:37:59
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

/*
 * Returns a full-duplex "stream" pipe (a UNIX domain socket)
 * with the two file descriptors returned in fd[0] and fd[1].
 */
int s_pipe(int fd[2]){
	return(socketpair(AF_UNIX, SOCK_STREAM, 0, fd));
}
