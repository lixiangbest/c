/*
 * =====================================================================================
 *
 *       Filename:  tcpserv05.c
 *
 *    Description:  tcp send binary data.
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

/*send binary data*/
struct args{
	long arg1;
	long arg2;
};

struct result{
	long sum;
};

/*add computing*/
void mystr_echo(int sockfd){
	ssize_t n;
	struct args args;
	struct result result;
	char line[MAXLINE];
	
	for(;;){
		/*read binary data*/
		if( (n = Readn(sockfd, &args, sizeof(args))) == 0)
			return;/*connection closed by other end*/
		result.sum = args.arg1 + args.arg2;
		/*write binary data*/
		Writen(sockfd, &result, sizeof(result));
	}
}

void sig_chld(int signo){
	pid_t pid;
	int stat;

	printf("start call sig_chld\n");
	while( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
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
		exit(0);
	}
	if( waitpid(childpid, NULL, 0) < 0){
		err_sys("waitpid error");
	}

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
		if( (childpid = Fork()) == 0){/*child process*/
			Close(listenfd);/*close listening socket*/
			mystr_echo(connfd);/*process the request*/
			exit(0);
		}
		Close(connfd);/*parent closes connected socket*/
	}
}
