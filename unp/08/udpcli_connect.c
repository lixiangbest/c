/*
 * =====================================================================================
 *
 *       Filename:  udpcli_connect.c
 *
 *    Description:  udp client use connect
 *
 *        Version:  1.0
 *        Created:  11/06/13 23:27:49
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
	/*struct sockaddr_in cliaddr;*/
	struct sockaddr_in servaddr;

	if(argc != 2)
		err_quit("usage: udpcli <IPaddress>");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	/*servaddr.sin_port = htons(7);*//*use the standard echo server port.*/
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
	
	/*upd bind defined port for test.*/
	/*
	bzero(&cliaddr, sizeof(cliaddr));
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	cliaddr.sin_port = htons(35887);
	Bind(sockfd, (SA*)&cliaddr, sizeof(cliaddr));
	*/

	dg_cli(stdin, sockfd, (SA*)&servaddr, sizeof(servaddr));
	exit(0);
}

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen){
	int n;
	char sendline[MAXLINE], recvline[MAXLINE + 1];

	Connect(sockfd, (SA*)pservaddr, servlen);
	while(Fgets(sendline, MAXLINE, fp) != NULL){
		Write(sockfd, sendline, strlen(sendline));
		n = Read(sockfd, recvline, MAXLINE);
		recvline[n] = 0;/*null terminate*/
		Fputs(recvline, stdout);
	}
}

