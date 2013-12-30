/*
 * =====================================================================================
 *
 *       Filename:  daytimetcpsrv2.c
 *
 *    Description:  daytime tcp server improve.
 *
 *        Version:  1.0
 *        Created:  11/24/13 22:09:22
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
	int listenfd, connfd;
	socklen_t len,addrlen;
	char buff[MAXLINE];
	time_t ticks;
	struct sockaddr_storage cliaddr;
	
	if(argc == 2){
		listenfd = Tcp_listen(NULL, argv[1], &addrlen);
	}else if(argc == 3){
		listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
	}else if(argc != 2){
		err_quit("usage: daytimetcpsrv2 [<host>] <service or port>");
	}
	printf("addrlen:%d\n", addrlen);
	for(;;){
		len = sizeof(cliaddr);
		connfd = Accept(listenfd, (SA*)&cliaddr, &len);
		printf("connection from %s\n", Sock_ntop((SA*)&cliaddr, len));

		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		Write(connfd, buff, strlen(buff));
		Close(connfd);
	}
	
	return 0;
}

