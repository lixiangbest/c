/*
 * =====================================================================================
 *
 *       Filename:  tcpclipipe.c
 *
 *    Description:  tcp client generate sigpipe
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

static int times = 0;

void mystr_cli(FILE *fp, int sockfd){
	char sendline[MAXLINE] = "from client!", recvline[MAXLINE];
	
	/*while(Fgets(sendline, MAXLINE, fp) != NULL){*/
	while(1){
		times++;
		sleep(2);
		Writen(sockfd, sendline, strlen(sendline));/*first write success, but second write generate sigpipe.*/
		sendline[strlen(sendline)] = 's';
		/*read line from server.*/
		if(Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");
		Fputs(recvline, stdout);
	}
}

/*when we write to a socket receiving RST will generate pipe singal.*/
void sig_pipe(int signo){
	if( signo == SIGPIPE )
		printf("times:%d catch sigpipe\n", times);
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
	servaddr.sin_port = htons(13);/*daytime server port*/
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);/*addr exchange.*/

	Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
	
	mystr_cli(stdin, sockfd);/*do it all*/
	
	exit(0);
}

