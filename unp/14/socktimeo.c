/*
 * =====================================================================================
 *
 *       Filename:  socktimeo.c
 *
 *    Description:  udp client for connecting timeout.
 *
 *        Version:  1.0
 *        Created:  11/03/13 17:28:15
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
	struct sockaddr_in servaddr;

	if(argc != 2)
		err_quit("usage: udpcli <IPaddress>");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	/*servaddr.sin_port = htons(SERV_PORT);*/
	servaddr.sin_port = htons(7);/*use the standard echo server port.*/
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	dg_cli(stdin, sockfd, (SA*)&servaddr, sizeof(servaddr));
	exit(0);
}

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen){
	int n;
	char sendline[MAXLINE], recvline[MAXLINE + 1];
	struct timeval tv;

	tv.tv_sec = 5;
	tv.tv_usec = 0;
	/*set sockopt timeout for read*/
	Setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
	while(Fgets(sendline, MAXLINE, fp) != NULL){
		Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
		
		n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
		if(n < 0){
			if(errno == EWOULDBLOCK){
				fprintf(stderr, "socket timeout\n");
				continue;
			}else
				err_sys("recvfrom error");
		}
		recvline[n] = 0;/*null terminate*/
		Fputs(recvline, stdout);
	}
}


