/*
 * =====================================================================================
 *
 *       Filename:  udpservloop1.c
 *
 *    Description:  udp server loop to expand the udp buffer.
 *
 *        Version:  1.0
 *        Created:  11/07/13 21:24:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

/*Singal handle function.*/
static void recvfrom_int(int);
static int count;

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
	Signal(SIGINT, recvfrom_int);

	n = 220 * 1024;
	Setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &n, sizeof(n));

	for(;;){
		len = clilen;
		Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
		count++;
	}
}

static void recvfrom_int(int signo){
	printf("\nreceived %d datagrams\n", count);
	exit(0);
}

