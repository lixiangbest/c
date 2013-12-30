/*
 * =====================================================================================
 *
 *       Filename:  tcpcli01.c
 *
 *    Description:  tcp cli01
 *
 *        Version:  1.0
 *        Created:  07/15/13 22:12:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

void mystr_cli(FILE *fp, int sockfd){
	char sendline[MAXLINE], recvline[MAXLINE];

	while(Fgets(sendline, MAXLINE, fp) != NULL){
		Writen(sockfd, sendline, strlen(sendline));
		if(Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");
		Fputs(recvline, stdout);
	}
}

int main(int argc, char **argv){
	int sockfd;
	struct sockaddr_in servaddr;
	struct linger ling;

	if(argc != 2){
		err_quit("usage: tcpcli <IPaddress>");
	}
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);/*addr exchange.*/

	/*set socket linger options*/
	ling.l_onoff = 1;
	ling.l_linger = 0;
	Setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &ling, sizeof(ling));

	Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
	
	mystr_cli(stdin, sockfd);/*do it all*/
	
	exit(0);
}
