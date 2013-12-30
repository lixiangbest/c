/*
 * =====================================================================================
 *
 *       Filename:  ruptime-dg.c
 *
 *    Description:  run time client use UDP.
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
#include<sys/socket.h>

#define BUFLEN 128
#define TIMEOUT 20

void sigalrm(int signo){
	printf("catch sigalrm");
}

void print_uptime(int sockfd, struct addrinfo *aip){
	int n;
	char buf[BUFLEN];

	buf[0] = 0;
	if(sendto(sockfd, buf, 1, 0, aip->ai_addr, aip->ai_addrlen) < 0)
		err_sys("sendto error");
	alarm(TIMEOUT);
	if((n = recvfrom(sockfd, buf, BUFLEN, 0, NULL, NULL)) < 0){
		if(errno != EINTR)
			alarm(0);
		err_sys("recv error");
	}
	alarm(0);
	write(STDOUT_FILENO, buf, n);
}

int main(int argc, char *argv[]){
	struct addrinfo *ailist, *aip;
	struct addrinfo hint;
	int sockfd, err;
	struct sigaction sa;

	if(argc != 2)
		err_quit("usage: ruptime hostname");

	sa.sa_handler = sigalrm;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if(sigaction(SIGALRM, &sa, NULL) < 0)
		err_sys("sigaction error");

	hint.ai_flags = 0;
	hint.ai_family = 0;
	hint.ai_socktype = SOCK_DGRAM;
	hint.ai_protocol = 0;
	hint.ai_addrlen = 0;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
	if((err = getaddrinfo(argv[1], "ruptime", &hint, &ailist)) != 0)
		err_quit("getaddrinfo error: %s", gai_strerror(err));

	for(aip = ailist; aip != NULL; aip = aip->ai_next){
		printf("aip->family:%d,aip->protocol:%d,service port:%d\n", aip->ai_family, aip->ai_protocol, ntohs(((struct sockaddr_in*)aip->ai_addr)->sin_port));
		if(aip->ai_family != AF_INET) continue;
		/*create socket*/
		if((sockfd = socket(aip->ai_family, SOCK_DGRAM, 0)) < 0){
			err = errno;
			perror("create socket!");
		}else{
			printf("socket creat successfully!\n");
			print_uptime(sockfd, aip);
			exit(0);
		}
	}

	fprintf(stderr, "can't connect to %s: %s\n", argv[1], strerror(err));
	exit(1);
}
