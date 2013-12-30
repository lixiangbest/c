/*
 * =====================================================================================
 *
 *       Filename:  01_findsvc.c
 *
 *    Description:  find service.
 *
 *        Version:  1.0
 *        Created:  06/10/13 17:57:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<netdb.h>
#include<arpa/inet.h>
#if defined(BSD) || defined(MACOS)
#include<sys/socket.h>
#include<netinet/in.h>
#endif

/*print addrinfo flags*/
void print_flags(struct addrinfo *aip){
	printf("flags:0x%x ",aip->ai_flags);
	if(aip->ai_flags == 0){
		printf(" 0");
	}else{
		if(aip->ai_flags & AI_PASSIVE)
			printf(" passive");
		if(aip->ai_flags & AI_CANONNAME)
			printf(" canon");
		if(aip->ai_flags & AI_NUMERICHOST)
			printf(" numhost");
#if defined(AI_NUMERICSERV)
		if(aip->ai_flags & AI_NUMERICSERV)
			printf(" numserv");
#endif
#if defined(AI_V4MAPPED)
		if(aip->ai_flags & AI_V4MAPPED)
			printf(" v4mapped");
#endif
#if defined(AI_ALL)
		if(aip->ai_flags & AI_ALL)
			printf(" all");
#endif
	}
}

void print_family(struct addrinfo *aip){
	printf(" family:%d ", aip->ai_family);
	switch(aip->ai_family){
		case AF_INET:
			printf("inet");
			break;
		case AF_INET6:
			printf("inet6");
			break;
		case AF_UNIX:
			printf("unix");
			break;
		case AF_UNSPEC:
			printf("unspecified");
			break;
		default:
			printf("unknow");
	}
}

void print_type(struct addrinfo *aip){
	printf(" type:%d ", aip->ai_socktype);
	switch(aip->ai_socktype){
		case SOCK_STREAM:
			printf("stream");
			break;
		case SOCK_DGRAM:
			printf("datagram");
			break;
		case SOCK_SEQPACKET:
			printf("seqpacket");
			break;
		case SOCK_RAW:
			printf("raw");
			break;
		default:
			printf("unkonwn (%d)", aip->ai_socktype);
	}
}

void print_protocol(struct addrinfo *aip){
	printf(" protocol:%d ", aip->ai_protocol);
	switch(aip->ai_protocol){
		case 0:
			printf("default");
			break;
		case IPPROTO_TCP:
			printf("TCP");
			break;
		case IPPROTO_UDP:
			printf("UDP");
			break;
		case IPPROTO_RAW:
			printf("raw");
			break;
		default:
			printf("unknown (%d)", aip->ai_protocol);
	}
}

int main(int argc, char *argv[]){
	struct addrinfo *ailist, *aip;
	struct addrinfo hint;
	struct sockaddr_in *sinp;
	const char *addr;
	int err;
	char abuf[INET_ADDRSTRLEN];

	printf("SOMAXCONN:%d\n", SOMAXCONN);
	printf("Macro __USE_GNU:%d,INET_DDRESTRLEN:%d\n", __USE_GNU, INET_ADDRSTRLEN);
	if(argc != 3){
		err_quit("usage: %s nodename service", argv[0]);
	}
	hint.ai_flags = AI_CANONNAME;
	hint.ai_family = 0;
	hint.ai_socktype = 0;
	hint.ai_protocol = 0;
	hint.ai_addrlen = 0;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
	if((err = getaddrinfo(argv[1], argv[2], &hint, &ailist)) != 0){
		err_quit("getaddrinfo error: %s", gai_strerror(err));
	}
	for(aip = ailist; aip != NULL; aip = aip->ai_next){
		print_flags(aip);
		print_family(aip);
		print_type(aip);
		print_protocol(aip);
		printf("\n\thost %s", aip->ai_canonname?aip->ai_canonname:"-");
		if(aip->ai_family == AF_INET){
			sinp = (struct sockaddr_in *)aip->ai_addr;
			addr = inet_ntop(AF_INET, &sinp->sin_addr, abuf, INET_ADDRSTRLEN);
			printf(" address %s", addr?addr:"unknown");
			printf(" port %d,%d", ntohs(sinp->sin_port), sinp->sin_port);
		}
		printf("\n");
	}

	exit(0);
}
