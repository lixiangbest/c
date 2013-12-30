/*
 * =====================================================================================
 *
 *       Filename:  ruptime.c
 *
 *    Description:  run time client.
 *
 *        Version:  1.0
 *        Created:  06/11/13 10:29:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<netdb.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/socket.h>

#define MAXADDRLEN 256
#define BUFLEN 128

extern int connect_retry(int, const struct sockaddr *, socklen_t);

void print_daytime(int sockfd){
	int n;
	char buf[BUFLEN];

	while((n = recv(sockfd, buf, BUFLEN, 0)) > 0)
		write(STDOUT_FILENO, buf, n);
	if(n < 0)
		err_sys("recv error");
}

int main(int argc, char *argv[]){
	struct addrinfo *ailist, *aip;
	struct addrinfo hint;
	int sockfd, err;

	if(argc != 2)
		err_quit("usage: ruptime hostname");
	hint.ai_flags = 0;
	hint.ai_family = 0;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = 0;
	hint.ai_addrlen = 0;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
	if((err = getaddrinfo(argv[1], "daytime", &hint, &ailist)) != 0)
		err_quit("getaddrinfo error: %s", gai_strerror(err));
	for(aip = ailist; aip != NULL; aip = aip->ai_next){
		printf("aip->family:%d,aip->protocol:%d,service port:%d\n", aip->ai_family, aip->ai_protocol, ntohs(((struct sockaddr_in*)aip->ai_addr)->sin_port));
		if(aip->ai_family != AF_INET) continue;
		/*create socket*/
		if((sockfd = socket(aip->ai_family, SOCK_STREAM, 0)) < 0){
			err = errno;
			perror("create socket!");
		}else{
			/*get sockfd owner*/
			printf("pid:%d, socket creat successfully!\n", fcntl(sockfd, F_GETOWN, 0));
		}
		/*socket connect server*/
		if(connect_retry(sockfd, aip->ai_addr, aip->ai_addrlen) < 0){
			err = errno;
		}else{
			print_daytime(sockfd);
			exit(0);
		}
	}
	fprintf(stderr, "can't connect to %s: %s\n", argv[1], strerror(err));
	exit(1);
}
