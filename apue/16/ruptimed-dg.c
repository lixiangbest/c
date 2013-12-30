/*
 * =====================================================================================
 *
 *       Filename:  ruptimed-dg.c
 *
 *    Description:  ruptime daemon use UDP.
 *
 *        Version:  1.0
 *        Created:  06/11/13 11:50:55
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
#include<syslog.h>
#include<sys/socket.h>

#define BUFLEN 128
#define MAXADDRLEN 256

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

extern int initserver(int, struct sockaddr *, socklen_t, int);

void serve(int sockfd){
	int n;
	socklen_t alen;
	FILE *fp;
	char buf[BUFLEN];
	char abuf[MAXADDRLEN];

	for(;;){
		alen = MAXADDRLEN;
		/*you must get the send source code.*/
		if((n = recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr *)abuf, &alen)) < 0){
			syslog(LOG_ERR, "ruptimed: recvfrom error: %s", strerror(errno));
			exit(1);
		}else{
			printf("Connect from %s\n", inet_ntoa((struct sockaddr_in *)abuf));
		}
		if((fp = popen("/usr/bin/uptime", "r")) == NULL){
			sprintf(buf, "error: %s\n", strerror(errno));
			sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)abuf, alen);
		}else{
			/*fetch data from the fp.*/
			if(fgets(buf, BUFLEN, fp) != NULL){
				sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)abuf, alen);
			}
			pclose(fp);
		}
	}
}

int main(int argc, char *argv[]){
	struct addrinfo *ailist, *aip;
	struct addrinfo hint;
	int sockfd, err, n;
	char *host;

	if(argc != 1)
		err_quit("usage: ruptimed");
#ifdef _SC_HOST_NAME_MAX
	n = sysconf(_SC_HOST_NAME_MAX);
	printf("n = %d\n", n);
	if(n < 0) /*best guess*/
#endif
		n = HOST_NAME_MAX;
	printf("HOST_NAME_MAX:%d\n", n);
	if((host = malloc(n)) == NULL)
		err_sys("malloc error");
	if(gethostname(host, n) < 0)
		err_sys("gethostname error");
	printf("The host:%s\n", host);
	/*daemonize("ruptimed");*/
	hint.ai_flags = AI_CANONNAME;
	hint.ai_family = 0;
	hint.ai_socktype = SOCK_DGRAM;
	hint.ai_protocol = 0;
	hint.ai_addrlen = 0;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
	if((err = getaddrinfo(host, "ruptime", &hint, &ailist)) != 0){
		syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s", gai_strerror(err));
		exit(1);
	}
	for(aip = ailist; aip != NULL; aip = aip->ai_next){
		printf("family %d\n", aip->ai_family);
		if(aip->ai_family == AF_INET){
			if((sockfd = initserver(SOCK_DGRAM, aip->ai_addr, aip->ai_addrlen, 0)) >= 0){
				/*printf("sockfd:%d\n", sockfd);*/
				serve(sockfd);
				exit(0);
			}
		}
	}
	exit(1);
}
