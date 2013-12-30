/*
 * =====================================================================================
 *
 *       Filename:  sock_select.c
 *
 *    Description:  socket contol, multiplex.
 *
 *        Version:  1.0
 *        Created:  06/12/13 22:12:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<fcntl.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define SERVPORT 3333
#define BACKLOG 10
#define MAX_CONNECTED_NO 10
#define MAXDATASIZE 100

int main(){
	struct sockaddr_in server_sockaddr, client_sockaddr;
	int sin_size, recvbytes;
	fd_set readset, writeset;
	int sockfd, client_fd, nread;
	char buf[MAXDATASIZE];

	/*create socket*/
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		err_sys("socket");
	}
	printf("socket success, sockfd=%d\n", sockfd);

	/*set sockaddr struct*/
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_port = htons(SERVPORT);
	server_sockaddr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(server_sockaddr.sin_zero), 8);

	/*bind port on local ip.*/
	if(bind(sockfd, (struct sockaddr*)&server_sockaddr, sizeof(struct sockaddr))==-1){
		err_sys("bind error");
	}
	printf("bind success!\n");

	/*listen*/
	if(listen(sockfd, BACKLOG) < 0){
		err_sys("listen error");
	}
	printf("listening...\n");

	/*select*/
	FD_ZERO(&readset);
	FD_SET(sockfd, &readset);/*add sockfd to readset*/

	while(1){
		sin_size = sizeof(struct sockaddr_in);
		/*accept client connecting.*/
		if(select(MAX_CONNECTED_NO, &readset, NULL, NULL, (struct timeval*)0) < 0){
			err_sys("select error");
		}
		if(FD_ISSET(sockfd, &readset) > 0){
			if((client_fd=accept(sockfd, (struct sockaddr*)&client_sockaddr, &sin_size))==-1){
				err_sys("accept error");
			}
			printf("accept success!\n");
			/*
			if((recvbytes = recv(client_fd, buf, MAXDATASIZE, 0)) == -1){
				err_sys("recv");
			}
			printf("recv success!\n");
			*/
			if((nread = read(client_fd, buf, MAXDATASIZE)) < 0){
				err_sys("read");
			}
			buf[nread] = '\0';
			printf("received client: %s\n", buf);
			/*
			while((nread = read(client_fd, buf, MAXDATASIZE)) > 0){
				printf("received client: %s\n", buf);
				write(STDOUT_FILENO, buf, nread);
			}
			*/
			/*close connect*/
			close(client_fd);
		}
	}
	exit(0);
}
