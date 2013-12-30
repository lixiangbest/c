/*
 * =====================================================================================
 *
 *       Filename:  tcpcli01_pipe.c
 *
 *    Description:  tcp cli01 generate sigpipe
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
#include "unp.h"

void mystr_cli(FILE *fp, int sockfd){
	char sendline[MAXLINE], recvline[MAXLINE];

	while(Fgets(sendline, MAXLINE, fp) != NULL){
		Writen(sockfd, sendline, 1);/*first write 1 byte.*/
		sleep(1);
		Writen(sockfd, sendline+1, strlen(sendline)-1);/*second write next bytes*/
		if(Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");
		Fputs(recvline, stdout);
	}
}

void sig_pipe(int signo){
	if( signo == SIGPIPE )
		printf("catch sigpipe\n");
}

int main(int argc, char **argv){
	int sockfd;
	struct sockaddr_in servaddr;

	if(argc != 2){
		err_quit("usage: tcpcli <IPaddress>");
	}
	Signal(SIGPIPE, sig_pipe);
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);/*addr exchange.*/

	Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
	
	mystr_cli(stdin, sockfd);/*do it all*/
	
	exit(0);
}

