/*
 * =====================================================================================
 *
 *       Filename:  spipe.c
 *
 *    Description:  socket pipe.
 *
 *        Version:  1.0
 *        Created:  06/13/13 21:25:37
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
 * with the two file descriptiors returned in fd[0] and fd[1].
 */
int s_pipe(int fd[2]){
	return(socketpair(AF_UNIX, SOCK_STREAM, 0, fd));
}
