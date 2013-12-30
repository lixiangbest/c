/*
 * =====================================================================================
 *
 *       Filename:  udpcli01.c
 *
 *    Description:  udp client.
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
	struct sockaddr_in cliaddr;
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
	socklen_t len;
	struct sockaddr *preply_addr;

	preply_addr = Malloc(servlen);
	while(Fgets(sendline, MAXLINE, fp) != NULL){
		Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
		/*no destination address: sendto error, Destination address required.*/
		/*Sendto(sockfd, sendline, strlen(sendline), 0, NULL, 0);*/

		len = servlen;
		/*n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);*/
		n = Recvfrom(sockfd, recvline, MAXLINE, 0, preply_addr, &len);/*get reply_addr*/
		/*datagram must from server address.*/
		printf("reply from %s\n", Sock_ntop(preply_addr, len));
		if(len != servlen || memcmp(pservaddr, preply_addr, len) != 0){
			/*printf("reply from %s(ignored)\n", Sock_ntop(preply_addr, len));*/
			continue;
		}
		recvline[n] = 0;/*null terminate*/
		Fputs(recvline, stdout);
	}
}

