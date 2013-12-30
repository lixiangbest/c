/*
 * =====================================================================================
 *
 *       Filename:  tcp_listen.c
 *
 *    Description:  tcp listen function
 *
 *        Version:  1.0
 *        Created:  11/24/13 18:42:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

int tcp_listen(const char *host, const char *serv, socklen_t *addrlenp){
	int listenfd, n;
	const int on = 1;
	struct addrinfo hints, *res, *ressave;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
		err_quit("tcp_listen error for %s, %s: %s", host, serv, gai_strerror(n));
	else
		printf("tcp_listen for %s\n", Sock_ntop(res->ai_addr, res->ai_addrlen));
	ressave = res;

	do{
		listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if(listenfd < 0)
			continue;/*error, try next one*/

		Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
		if(bind(listenfd, res->ai_addr, res->ai_addrlen)==0)
			break;/*success*/

		Close(listenfd);/*bind error, close and try next one*/
	}while( (res = res->ai_next) != NULL);

	if(res == NULL){/*errno from final socket() or bind()*/
		err_sys("tcp_listen error for %s, %s", host, serv);
	}
	Listen(listenfd, LISTENQ);

	if(addrlenp)
		*addrlenp = res->ai_addrlen;/*return size of protocol address*/

	freeaddrinfo(ressave);
	return listenfd;
}
/*end tcp_listen*/

/*
 * We place the wrapper function here, not in wraplib.c, because some XTI programs need to include wraplib.c, and it also defines a Tcp_listen() function.*/
int Tcp_listen(const char *host, const char *serv, socklen_t *addrlenp){
	return(tcp_listen(host, serv, addrlenp));
}

