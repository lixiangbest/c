/*************************************************************************
	> File Name: unixstrserv01.c
	> Description: 
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月14日 星期六 08时49分33秒
 ************************************************************************/
#include "unp.h"

int main(int argc, char **argv){
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_un cliaddr, servaddr;
	void sig_chld(int);

	listenfd = Socket(AF_LOCAL, SOCK_STREAM, 0);
	unlink(UNIXSTR_PATH);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UNIXSTR_PATH);
	
	/*Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));*/
	Bind(listenfd, (SA*)&servaddr, SUN_LEN(&servaddr));/*equal to the up line.*/
	Listen(listenfd, LISTENQ);
	Signal(SIGCHLD, sig_chld);

	for(;;){
		clilen = sizeof(cliaddr);
		if( (connfd = accept(listenfd, (SA*)&cliaddr, &clilen))<0 ){
			if(errno == EINTR)
				continue;/*back to for()*/
			else
				err_sys("accept error");
		}
		if( (childpid = Fork()) == 0){/*child process*/
			Close(listenfd);/*close listening socket*/
			str_echo(connfd);/*process request*/
			exit(0);
		}
		Close(connfd);/*parent closes connected socket*/
	}
	return 0;
}

void sig_chld(int signo){
	pid_t pid;
	int stat;
	while( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated\n", pid);
	return;
}
