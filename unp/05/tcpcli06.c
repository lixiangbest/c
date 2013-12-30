/*
 * =====================================================================================
 *
 *       Filename:  tcpcli06.c
 *
 *    Description:  read and write binary data.
 *
 *        Version:  1.0
 *        Created:  07/15/13 22:12:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

struct args{
	long arg1;
	long arg2;
};

struct result{
	long sum;
};

void mystr_cli(FILE *fp, int sockfd){
	char sendline[MAXLINE];
	struct args args;
	struct result result;

	while(Fgets(sendline, MAXLINE, fp) != NULL){
		if(sscanf(sendline, "%ld%ld", &args.arg1, &args.arg2)!=2){
			printf("invalid input: %s", sendline);
			continue;
		}
		/*send binary data from stdio*/
		Writen(sockfd, &args, sizeof(args));
		/*read processed binary data from tcp server*/
		if(Readn(sockfd, &result, sizeof(result)) == 0)
			err_quit("str_cli: server terminated prematurely");
		printf("%ld\n", result.sum);
	}
}

int main(int argc, char **argv){
	int sockfd;
	struct sockaddr_in servaddr;

	if(argc != 2){
		err_quit("usage: tcpcli <IPaddress>");
	}
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);/*addr exchange.*/

	Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
	
	mystr_cli(stdin, sockfd);/*do it all*/
	
	exit(0);
}

