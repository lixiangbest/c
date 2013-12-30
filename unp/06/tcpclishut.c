/*
 * =====================================================================================
 *
 *       Filename:  tcpclishut.c
 *
 *    Description:  tcpcli test to shut the RD.
 *
 *        Version:  1.0
 *        Created:  07/24/13 22:35:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

int main(int argc, char *argv[]){
	int sockfd;
	char buf[MAXLINE];
	struct sockaddr_in servaddr;
	int n, i = 0;

	if(argc != 2){
		err_quit("usage: tcpcli <IPaddress>");
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);/*SERV_PORT*/
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);/*addr exchange.*/

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));

	shutdown(sockfd, SHUT_WR);
	while(i < 3){
		if( (n = read(sockfd, buf, 3)) > 0)
			Write(STDOUT_FILENO, buf, n);
		sleep(3);
		i++;
	}

	exit(0);
}

