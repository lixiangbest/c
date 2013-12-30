/*
 * =====================================================================================
 *
 *       Filename:  rcvbuf.c
 *
 *    Description:  receive buffer
 *
 *        Version:  1.0
 *        Created:  10/31/13 22:09:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"
#include<netinet/tcp.h> /*for TCP_MAXSEG*/

int main(int argc, char **argv){
	int sockfd, rcvbuf, mss;
	socklen_t len;
	struct sockaddr_in servaddr;

	if(argc != 2)
		err_quit("Usage: rcvbuf <IPaddress>");
	
	sockfd = Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	len = sizeof(rcvbuf);
	Getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &rcvbuf, &len);
	len = sizeof(mss);
	Getsockopt(sockfd, IPPROTO_TCP, TCP_MAXSEG, &mss, &len);
	printf("defaults: SO_RCVBUF = %d, MSS = %d\n", rcvbuf, mss);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(80);/*daytime server;http server*/
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
	
	len = sizeof(rcvbuf);
	Getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &rcvbuf, &len);
	len = sizeof(mss);
	Getsockopt(sockfd, IPPROTO_TCP, TCP_MAXSEG, &mss, &len);
	printf("after connect: SO_RCVBUF = %d, MSS = %d\n", rcvbuf, mss);

	exit(0);
}


