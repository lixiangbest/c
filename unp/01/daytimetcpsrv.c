/*
 * =====================================================================================
 *
 *       Filename:  daytimetcpsrv.c
 *
 *    Description:  daytime tcp server.
 *
 *        Version:  1.0
 *        Created:  07/07/13 22:02:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"
#include<time.h>

int main(int argc, char **argv){
	int listenfd, connfd, i;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	time_t ticks;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(8080);/*daytime server*/

	Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	for(;;){
		connfd = Accept(listenfd, (SA*)NULL, NULL);/*don't concern the client address*/

		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		/*
		Write(connfd, buff, strlen(buff));
		*/
		for(i = 0; i < strlen(buff); i++)
			Write(connfd, &buff[i], 1);

		Close(connfd);
	}
}

