/*************************************************************************
	> File Name: lib/dg_cli.c
	> Description: 
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月14日 星期六 22时10分40秒
 ************************************************************************/
#include "unp.h"

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen){
	int n;
	char sendline[MAXLINE], recvline[MAXLINE + 1];

	while(Fgets(sendline, MAXLINE, fp) != NULL){
		Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
		n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
		recvline[n] = 0;/*null terminate*/
		Fputs(recvline, stdout);
	}
}
