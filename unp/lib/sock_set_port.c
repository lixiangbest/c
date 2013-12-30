/*
 * =====================================================================================
 *
 *       Filename:  sock_set_port.c
 *
 *    Description:  socket set port.
 *
 *        Version:  1.0
 *        Created:  11/28/13 23:32:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

void sock_set_port(struct sockaddr *sa, socklen_t salen, int port){
	switch(sa->sa_family){
		case AF_INET:{
			struct sockaddr_in *sin = (struct sockaddr_in *)sa;
			sin->sin_port = port;
			return;
		}
#ifdef IPV6
		case AF_INET6:{
			struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;
			sin6->sin6_port = port;
			return;
		}
#endif
	}
	return;
}


