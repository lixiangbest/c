/*
 * =====================================================================================
 *
 *       Filename:  udpservbig.c
 *
 *    Description:  udp server receive and send big datagram.
 *
 *        Version:  1.0
 *        Created:  11/09/13 16:48:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

#undef MAXLINE
#define MAXLINE 0xffff - 20 - 8

int main(int argc, char **argv){
	int sockfd;
	struct sockaddr_in servaddr, cliaddr;
	
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	
	Bind(sockfd, (SA*)&servaddr, sizeof(servaddr));

	dg_echo(sockfd, (SA*)&cliaddr, sizeof(cliaddr));

	return 0;
}

void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen){
	int n, buf_size;
	socklen_t len;
	char mesg[MAXLINE];
	ssize_t s_n;/*sendto size*/

	/*set sockfd buffer.*/
	buf_size = 70000;
	Setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &buf_size, sizeof(buf_size));
	Setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &buf_size, sizeof(buf_size));

	for(;;){
		len = clilen;
		n = Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
		s_n = sendto(sockfd, mesg, n, 0, pcliaddr, len);
		printf("recv: %d, sendto: %d\n", n, s_n);
	}
}

