/*
 * =====================================================================================
 *
 *       Filename:  tcp_connect.c
 *
 *    Description:  tcp connect.
 *
 *        Version:  1.0
 *        Created:  11/24/13 17:00:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
/*include tcp_connect*/
#include "unp.h"

int tcp_connect(const char *host, const char *serv){
	int sockfd, n;
	struct addrinfo hints, *res, *ressave;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
		err_quit("tcp_connect error for %s, %s: %s", host, serv, gai_strerror(n));
	ressave = res;
	
	do{
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if(sockfd < 0)
			continue;/*ignore this one*/

		if(connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
			break;

		Close(sockfd);/*ignore this one*/
	}while( (res = res->ai_next) != NULL);

	if(res == NULL) /*errno set from final connect()*/
		err_sys("tcp_connect error for %s, %s", host, serv);

	freeaddrinfo(ressave);

	return sockfd;
}
/*end tcp_connect*/

/*
 * We place the wrapper function here, not in wraplib.c, because some XTI
 * programs need to include wraplib.c, and it also defines a Tcp_connect() function.
 */
int Tcp_connect(const char *host, const char *serv){
	return(tcp_connect(host, serv));
}

