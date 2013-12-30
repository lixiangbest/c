/*
 * =====================================================================================
 *
 *       Filename:  sock_cntl.c
 *
 *    Description:  socket contol.
 *    				socket block; socket async
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
	int sin_size, recvbytes, flags;
	int sockfd, client_fd;
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

	/*fcntl function, handling mutil I/O*/
	if((flags = fcntl(sockfd, F_GETFL, 0)) < 0){
		err_sys("fcntl F_GETFL");
	}
	flags |= O_NONBLOCK;/*I/O unblock,Resource temporarily unavailable*/
	/*flags |= O_ASYNC;*//*I/O async, until receive signal*/
	if(fcntl(sockfd, F_SETFL, flags) < 0){
		err_sys("set O_NONBLOCK");
	}

	while(1){
		sin_size = sizeof(struct sockaddr_in);
		/*accept client connecting.*/
		if((client_fd = accept(sockfd, (struct sockaddr*)&client_sockaddr, &sin_size)) < 0){
			err_sys("accept");
		}
		printf("accept success!\n");
		if((recvbytes = recv(client_fd, buf, MAXDATASIZE, 0)) == -1){
			err_sys("recv");
		}
		printf("recv success!\n");
		if(read(client_fd, buf, MAXDATASIZE) < 0){
			err_sys("read");
		}
		printf("received a connection : %s", buf);

		/*close connect*/
		close(client_fd);
		exit(1);
	}
	/*exit(0);*/
}

