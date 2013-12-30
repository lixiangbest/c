/*
 * =====================================================================================
 *
 *       Filename:  tcpservpoll.c
 *
 *    Description:  tcp server poll version.
 *
 *        Version:  1.0
 *        Created:  07/17/13 00:10:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"
#include<limits.h> /*for OPEN_MAX*/
#define OPEN_MAX 1024

int main(int argc, char **argv){
	int i, maxi, listenfd, connfd, sockfd;
	int nready;/*select return value*/
	ssize_t n;
	char buf[MAXLINE];
	socklen_t clilen;
	struct pollfd client[OPEN_MAX];
	struct sockaddr_in cliaddr, servaddr;

	printf("OPEN_MAX: 0x%x\n", OPEN_MAX);

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));
	Listen(listenfd, LISTENQ);

	client[0].fd = listenfd;/*initialize*/
	client[0].events = POLLRDNORM;
	for(i = 1; i < OPEN_MAX; i++){
		client[i].fd = -1;/*-1 indicates available entry*/
	}
	maxi = 0;/*max index into client[] array*/

	for(;;){
		nready = Poll(client, maxi+1, INFTIM);

		if(client[0].revents & POLLRDNORM){/*new client connection*/
			clilen = sizeof(cliaddr);
			connfd = Accept(listenfd, (SA*)&cliaddr, &clilen);

			for(i = 0; i < OPEN_MAX; i++){
				if(client[i].fd < 0){
					client[i].fd = connfd;/*save descriptor*/
					break;
				}
			}
			if(i == OPEN_MAX)
				err_quit("too many clients");
			client[i].events = POLLRDNORM;

			if(i > maxi) maxi = i;/*max index in client[] array*/
			if(--nready <= 0) continue;/*no more readable descriptors*/
		}

		for(i = 1; i <= maxi; i++){/*check all clients for data*/
			if( (sockfd = client[i].fd) < 0)	continue;
			if(client[i].revents & (POLLRDNORM | POLLERR)){
				if( (n = read(sockfd, buf, MAXLINE)) < 0){
					if(errno == ECONNRESET){
						/*connection reset by client*/
						Close(sockfd);
						client[i].fd = -1;
					}else
						err_sys("read error");
				}else if(n == 0){
					/*connection reset by client*/
					Close(sockfd);
					client[i].fd = -1;
				}else{
					Writen(sockfd, buf, n);
				}
				if(--nready <= 0)	break;/*no more readable descriptors*/
			}
		}
	}
}

