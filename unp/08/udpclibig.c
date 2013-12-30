/*
 * =====================================================================================
 *
 *       Filename:  udpclibig.c
 *
 *    Description:  udp client send and recevie big datagram.
 *
 *        Version:  1.0
 *        Created:  11/09/13 16:13:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<math.h>
#include "unp.h"

#undef MAXLINE
#define MAXLINE 65536 - 1 - 20 -8

int main(int argc, char **argv){
	int sockfd;
	struct sockaddr_in servaddr;

	if(argc != 2)
		err_quit("usage: udpcli <IPaddress>");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	/*servaddr.sin_port = htons(7);*//*use the standard echo server port.*/
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	dg_cli(stdin, sockfd, (SA*)&servaddr, sizeof(servaddr));
	exit(0);
}

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen){
	int size;
	char sendline[MAXLINE], recvline[MAXLINE + 1];
	ssize_t n;
	
	size = 70000;
	Setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &size, sizeof(size));
	Setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));

	Sendto(sockfd, sendline, MAXLINE, 0, pservaddr, servlen);
	n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);/*get reply_addr*/
	printf("received %d bytes\n", n);
}

