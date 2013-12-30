/*
 * =====================================================================================
 *
 *       Filename:  tcpcliselect02.c
 *
 *    Description:  tcp cli select version 2.
 *    				solve the line buffer problem.
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
/*Use standard echo server; baseline measurements for nonblocking version*/
#include "unp.h"

void mystr_cli(FILE *fp, int sockfd){
	int maxfdp, stdineof;
	fd_set rset;
	char buf[MAXLINE];
	int n;

	stdineof = 0;
	FD_ZERO(&rset);
	for(;;){
		if(stdineof == 0)
			FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdp = max(fileno(fp), sockfd) + 1;
		Select(maxfdp, &rset, NULL, NULL, NULL);

		if(FD_ISSET(sockfd, &rset)){/*socket is readable*/
			/*printf("socket is readable:\n");*/
			fprintf(stderr, "sockfd stdineof = %d\n", stdineof);
			if( (n = Read(sockfd, buf, MAXLINE)) == 0){
				if(stdineof == 1)
					return;/*normal termination*/
				else 
					err_quit("str_cli: server terminated prematurely");
			}
			Write(fileno(stdout), buf, n);
		}

		if(FD_ISSET(fileno(fp), &rset)){/*input is readable*/
			fprintf(stderr, "stdin stdineof = %d\n", stdineof);
			if( (n = Read(fileno(fp), buf, MAXLINE)) == 0){
				stdineof = 1;
				Shutdown(sockfd, SHUT_WR);/*send FIN, close write.*/
				FD_CLR(fileno(fp), &rset);
				continue;
			}
			Writen(sockfd, buf, n);
		}
	}
}

int main(int argc, char **argv){
	int sockfd;
	struct sockaddr_in servaddr;

	if(argc != 2){
		err_quit("usage: tcpcli <IPaddress>");
	}
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);/*SERV_PORT 7*/
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);/*addr exchange.*/

	Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
	
	mystr_cli(stdin, sockfd);/*do it all*/
	
	exit(0);
}

