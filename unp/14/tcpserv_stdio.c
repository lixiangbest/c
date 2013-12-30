/*
 * =====================================================================================
 *
 *       Filename:  tcpserv_stdio.c
 *
 *    Description:  tcp server use the stdio library.
 *
 *        Version:  1.0
 *        Created:  07/15/13 21:44:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

void mystr_echo(int sockfd){
	char line[MAXLINE];
	FILE *fpin, *fpout;

	fpin = Fdopen(sockfd, "r");
	fpout = Fdopen(sockfd, "w");
	
	while(Fgets(line, MAXLINE, fpin) != NULL){
		/*setvbuf(fpout, line, _IOLBF, MAXLINE);*//*set line buffer.*/
		Fputs(line, fpout);
		/*fflush(fpout);*//*file flush*/
	}
}

int main(int argc, char **argv){
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));
	Listen(listenfd, LISTENQ);

	for(;;){
		clilen = sizeof(cliaddr);
		connfd = Accept(listenfd, (SA*)&cliaddr, &clilen);
		if( (childpid = Fork()) == 0){/*child process*/
			Close(listenfd);/*close listening socket*/
			mystr_echo(connfd);/*process the request*/
			exit(0);
		}
		Close(connfd);/*parent closes connected socket*/
	}
	return 0;
}
