/*
 * =====================================================================================
 *
 *       Filename:  daytimetcpcli.c
 *
 *    Description:  day time tcp client.
 *
 *        Version:  1.0
 *        Created:  11/24/13 17:53:41
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
	int sockfd, n;
	char recvline[MAXLINE+1];
	socklen_t len;
	struct sockaddr_storage ss;

	if(argc != 3){
		err_quit("usage: daytimetcpcli <hostname/IPaddress> <service/port#>");
	}
	sockfd = Tcp_connect(argv[1], argv[2]);

	len = sizeof(ss);
	Getpeername(sockfd, (SA*)&ss, &len);
	printf("connected to %s\n", Sock_ntop_host((SA*)&ss, len));

	while( (n = Read(sockfd, recvline, MAXLINE)) > 0){
		recvline[n] = 0;/*null terminate*/
		Fputs(recvline, stdout);
	}
	exit(0);
}

