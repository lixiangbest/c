/*************************************************************************
	> File Name: tcpcli02.c
	> Description: tcp client for non-block
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月20日 星期五 03时52分39秒
 ************************************************************************/
#include "unp.h"

int main(int argc, char **argv){
	int sockfd;
	struct sockaddr_in servaddr;

	if(argc != 2)
		err_quit("usage: tcpcli <IPaddress>");

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(7);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));

	str_cli(stdin, sockfd);/*do it all*/
	
	exit(0);
}
