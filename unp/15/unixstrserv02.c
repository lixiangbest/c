/*************************************************************************
	> File Name: unixstrserv02.c
	> Description: 
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月17日 星期二 09时30分51秒
 ************************************************************************/
#include "unp.h"

int main(int argc, char **argv){
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_un cliaddr, servaddr;
	void sig_chld(int);
	const int on = 1;

	listenfd = Socket(AF_LOCAL, SOCK_STREAM, 0);

	unlink(UNIXSTR_PATH);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UNIXSTR_PATH);

	Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	Signal(SIGCHLD, sig_chld);

	for(;;){
		clilen = sizeof(cliaddr);
		if( (connfd = accept(listenfd, (SA*)&cliaddr, &clilen)) < 0){
			if(errno == EINTR)
				continue;/*back to for()*/
			else
				err_sys("accept error");
		}

		/*you must set the sockopt in Linux, then you can read cred.*/
		if(setsockopt(connfd, SOL_SOCKET, SO_PASSCRED, &on, sizeof(on)))
			err_sys("setsockopt error");

		if( (childpid = Fork()) == 0){/*child process*/
			Close(listenfd);/*close listening socket*/
			str_echo(connfd);/*process the request*/
			exit(0);
		}
		Close(connfd);/*parent closes connected socket*/
	}
}

void sig_chld(int signo){
	pid_t pid;
	int stat;
	while( (pid = waitpid(-1, &stat, WNOHANG)) > 0 )
		printf("child %d terminated\n", pid);
	return;
}
