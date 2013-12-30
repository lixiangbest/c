/*
 * =====================================================================================
 *
 *       Filename:  udpserv01.c
 *
 *    Description:  udp server first version.
 *
 *        Version:  1.0
 *        Created:  11/03/13 16:08:11
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
	int n;
	socklen_t len;
	char mesg[MAXLINE];

	for(;;){
		len = clilen;
		printf("clilen %d, len %d\n", clilen, len);
		n = Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
		Sendto(sockfd, mesg, n, 0, pcliaddr, len);
	}
}
