/*
 * =====================================================================================
 *
 *       Filename:  daytimetcpcli.c
 *
 *    Description:  daytime tcp client.
 *
 *        Version:  1.0
 *        Created:  07/02/13 21:49:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

int main(int argc, char **argv){
	int sockfd, n, counter = 0;
	char recvline[MAXLINE+1];
	struct sockaddr_in servaddr, cliaddr;
	socklen_t len;

	if(argc != 2)
		err_quit("usage: a.out <IPaddress>");

	if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");
	
	printf("s_addr = INADDR_ANY = %x, getenv(LISTENQ):%s\n", INADDR_ANY, getenv("LISTENQ"));
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(1313);/*daytime server 13, host to network short int.*/
	printf("seraddr.sin_port:0x%x, char address:%s\n", htons(13), argv[1]);
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);

	if(connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");
	
	/*get local addr after connecting.*/
	cliaddr.sin_family = AF_INET;
	len = sizeof(cliaddr);
	Getsockname(sockfd, (SA*)&cliaddr, &len);
	printf("local_addr: %s\n", Sock_ntop((SA*)&cliaddr, len));

	while( (n = read(sockfd, recvline, MAXLINE)) > 0){
		counter++;/*count the read > 0 times*/
		recvline[n] = 0;/*null terminate*/
		if(fputs(recvline, stdout) == EOF){
			err_sys("fputs error");
		}
	}
	printf("counter = %d\n", counter);
	if(n < 0)
		err_sys("read error");

	exit(0);
}

