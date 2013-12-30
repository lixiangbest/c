/*
 * =====================================================================================
 *
 *       Filename:  tcpserv01.c
 *
 *    Description:  tcp server 01.c
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
	ssize_t n;
	char buf[MAXLINE];

again:
	while( (n = read(sockfd, buf, MAXLINE)) > 0)
		Writen(sockfd, buf, n);

	if(n < 0 && errno == EINTR)
		goto again;
	else if(n < 0)
		err_sys("str_echo: read error");
}

void sig_chld(int signo){
	pid_t pid;
	int stat;

	pid = wait(&stat);
	printf("child %d terminated\n", pid);
	return;
}

int main(int argc, char **argv){
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	if( (childpid = fork()) < 0){
		err_sys("fork error");
	}else if(childpid == 0){/*child*/
		printf("child listenfd addr: 0x%x\n", &listenfd);
		exit(0);
	}
	if( waitpid(childpid, NULL, 0) < 0){
		err_sys("waitpid error");
	}
	printf("parent listenfd addr: 0x%x\n", &listenfd);

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));
	Listen(listenfd, LISTENQ);

	Signal(SIGCHLD, sig_chld);

	for(;;){
		clilen = sizeof(cliaddr);
		connfd = Accept(listenfd, (SA*)&cliaddr, &clilen);
		/*
		 * if( (connfd = accept(listenfd, (SA*)&cliaddr, &clilen)) < 0){
		 *     if(errno == EINTR)
		 *        continue;//back to for()
		 *	   else
		 *	  	  err_sys("accept error");
		 */
		if( (childpid = Fork()) == 0){/*child process*/
			Close(listenfd);/*close listening socket*/
			mystr_echo(connfd);/*process the request*/
			exit(0);
		}
		Close(connfd);/*parent closes connected socket*/
	}
}
