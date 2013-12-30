/*
 * =====================================================================================
 *
 *       Filename:  udp_server.c
 *
 *    Description:  udp server.
 *
 *        Version:  1.0
 *        Created:  11/24/13 23:49:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

int udp_server(const char *host, const char *serv, socklen_t *addrlenp){
	int sockfd, n;
	struct addrinfo hints, *res, *ressave;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
		err_quit("udp_connect error for %s, %s: %s", host, serv, gai_strerror(n));
	ressave = res;
	
	do{
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if(sockfd < 0)
			continue;/*ignore this one*/
		
		if(bind(sockfd, res->ai_addr, res->ai_addrlen) == 0)
			break;/*success*/

		Close(sockfd);/*ingore this one*/
	}while( (res = res->ai_next) != NULL);
	
	if(res == NULL) /*errno set from final connect()*/
		err_sys("udp_server error for %s, %s", host, serv);

	if(addrlenp)
		*addrlenp = res->ai_addrlen;/*return size of protocol address*/

	freeaddrinfo(ressave);

	return sockfd;
}
/*end udp_server*/

int Udp_server(const char *host, const char *serv, socklen_t *addrlenp){
	return(udp_server(host, serv, addrlenp));
}

