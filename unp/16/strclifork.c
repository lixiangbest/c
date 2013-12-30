/*************************************************************************
	> File Name: 16/strclifork.c
	> Description: str_cli function when fork.
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月19日 星期四 09时40分04秒
 ************************************************************************/
#include "unp.h"

void str_cli(FILE *fp, int sockfd){
	pid_t pid;
	char sendline[MAXLINE], recvline[MAXLINE];

	if( (pid = Fork()) == 0 ){/*child: server->stdout*/
		while(Readline(sockfd, recvline, MAXLINE)>0)
			Fputs(recvline, stdout);
		kill(getppid(), SIGTERM);/*in case parent still running*/
		exit(0);
	}

	/*parent: stdin->server*/
	while(Fgets(sendline, MAXLINE, fp) != NULL)
		Writen(sockfd, sendline, strlen(sendline));

	Shutdown(sockfd, SHUT_WR);/*EOF on stdin, send FIN*/
	pause();
	return;
}

