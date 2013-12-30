/*
 * =====================================================================================
 *
 *       Filename:  tcpcli04.c
 *
 *    Description:  tcp client version4.
 *
 *        Version:  1.0
 *        Created:  07/16/13 23:37:44
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
	int i, sockfd[5];/*connent server 5 times meanwhile.*/
	struct sockaddr_in servaddr;

	if(argc != 2){
		err_quit("usage: tcpcli <IPaddress>");
	}
	for(i = 0; i < 5; i++){
		sockfd[i] = Socket(AF_INET, SOCK_STREAM, 0);

		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(SERV_PORT);
		Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);/*addr exchange.*/

		Connect(sockfd[i], (SA*)&servaddr, sizeof(servaddr));
	}
	close(sockfd[1]);
	str_cli(stdin, sockfd[0]);/*do it all*/
	
	exit(0);
}

