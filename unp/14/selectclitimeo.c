/*
 * =====================================================================================
 *
 *       Filename:  selectclitimeo.c
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
	servaddr.sin_port = htons(SERV_PORT);
	/*servaddr.sin_port = htons(7);*//*use the standard echo server port.*/
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	dg_cli(stdin, sockfd, (SA*)&servaddr, sizeof(servaddr));
	exit(0);
}

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen){
	int n;
	char sendline[MAXLINE], recvline[MAXLINE + 1];

	while(Fgets(sendline, MAXLINE, fp) != NULL){
		Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
		/*use the select function timeout effect.*/
		if(Readable_timeo(sockfd, 5) == 0){
			/*fprintf(stderr, "socket timeout\n");*/
			err_quit("socket timeout\n");
		}else{
			n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
			recvline[n] = 0;/*null terminate*/
			Fputs(recvline, stdout);
		}
	}
}

