/*
 * =====================================================================================
 *
 *       Filename:  udpcli_if.c
 *
 *    Description:  udp client interface.
 *
 *        Version:  1.0
 *        Created:  11/07/13 22:32:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

int main(int argc, char **argv){
	int sockfd;
	socklen_t len;
	struct sockaddr_in cliaddr, servaddr;

	if(argc != 2)
		err_quit("usage: udpcli <IPaddress>");

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));

	len = sizeof(cliaddr);
	Getsockname(sockfd, (SA*)&cliaddr, &len);
	printf("local address %s\n", Sock_ntop((SA*)&cliaddr, len));

	exit(0);
}

