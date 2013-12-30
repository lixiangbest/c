/*
 * =====================================================================================
 *
 *       Filename:  tcpcli01.c
 *
 *    Description:  tcpcli test to hang up the server process.
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
	char buf[MAXLINE] = "lixiang";
	struct sockaddr_in servaddr;

	if(argc != 2){
		err_quit("usage: tcpcli <IPaddress>");
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);/*SERV_PORT*/
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);/*addr exchange.*/

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));

	Write(sockfd, buf, strlen(buf));
	pause();

	exit(0);
}

