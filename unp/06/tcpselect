/*
 * =====================================================================================
 *
 *       Filename:  tcpcliselect01.c
 *
 *    Description:  tcp cli select.
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
	int maxfdp;
	/*int cflags;*/
	fd_set rset;
	char sendline[MAXLINE], recvline[MAXLINE];

	/*set fd nonblock*/
	/*cflags = fcntl(fileno(fp), F_GETFL, 0);*/
	/*fcntl(fileno(fp), F_SETFL, cflags|O_NONBLOCK);*/
	/*set no buffer*/
	setbuf(fp, NULL);

	FD_ZERO(&rset);
	for(;;){
		FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdp = max(fileno(fp), sockfd) + 1;
		Select(maxfdp, &rset, NULL, NULL, NULL);

		if(FD_ISSET(sockfd, &rset)){/*socket is readable*/
			/*printf("socket is readable:\n");*/
			if(Readline(sockfd, recvline, MAXLINE) == 0)
				err_quit("str_cli: server terminated prematurely");
			Fputs(recvline, stdout);
		}

		if(FD_ISSET(fileno(fp), &rset)){/*input is readable*/
			/*printf("input is readable:\n");*/
			if(Fgets(sendline, MAXLINE, fp) == NULL)
				return;/*all done*/
			Writen(sockfd, sendline, strlen(sendline));
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

