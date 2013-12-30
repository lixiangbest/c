/*************************************************************************
	> File Name: lib/dg_echo.c
	> Description: 
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月14日 星期六 21时28分40秒
 ************************************************************************/
#include "unp.h"

void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen){
	int n;
	socklen_t len;
	char mesg[MAXLINE];

	for(;;){
		len = clilen;
		n = Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);

		Sendto(sockfd, mesg, n, 0, pcliaddr, len);
	}
}
