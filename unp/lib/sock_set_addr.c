/*
 * =====================================================================================
 *
 *       Filename:  sock_set_addr.c
 *
 *    Description:  socket set address.
 *
 *        Version:  1.0
 *        Created:  11/28/13 23:28:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

void sock_set_addr(struct sockaddr *sa, socklen_t salen, const void *addr){
	switch(sa->sa_family){
		case AF_INET:{
			struct sockaddr_in *sin = (struct sockaddr_in *)sa;
			memcpy(&sin->sin_addr, addr, sizeof(struct in_addr));
			return;
		}
#ifdef IPV6
		case AF_INET6:{
			struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;
			memcpy(&sin6->sin6_addr, addr, sizeof(struct in6_addr));
			return;
		}
#endif
	}
	return;
}

