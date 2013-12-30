/*
 * =====================================================================================
 *
 *       Filename:  udpcli01.c
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

static void sig_alrm(int);

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

	Signal(SIGALRM, sig_alrm);

	while(Fgets(sendline, MAXLINE, fp) != NULL){
		Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
		
		alarm(5);/*set timeout for recvfrom*/
		if( (n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL)) < 0){
			if(errno == EINTR)
				fprintf(stderr, "socket timeout\n");
			else
				err_sys("recvfrom error");
		}else{
			alarm(0);
			recvline[n] = 0;/*null terminate*/
			Fputs(recvline, stdout);
		}
	}
}

static void sig_alrm(int signo){
	printf("catch sig_alrm.\n");
	return;
}

