/*
 * =====================================================================================
 *
 *       Filename:  daytimeudpcli1.c
 *
 *    Description:  daytime udp client 1.
 *
 *        Version:  1.0
 *        Created:  11/24/13 23:10:15
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
	char recvline[MAXLINE + 1];
	socklen_t salen;
	struct sockaddr *sa;
	
	if(argc != 3){
		err_quit("usage: daytimeudpcli1 <hostname/IPaddress> <service/port#>");
	}
	sockfd = Udp_client(argv[1], argv[2], (void **)&sa, &salen);
	printf("sizeof sa:%d, salen:%d\n", sizeof(*sa), salen);
	printf("sending to %s\n", Sock_ntop_host(sa, salen));
	//Sendto(sockfd, "", 1, 0, sa, salen);/*send 1-byte datagram*/
	Sendto(sockfd, "", 0, 0, sa, salen);
	
	n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
	recvline[n] = '\0';/*null terminate*/
	Fputs(recvline, stdout);

	return 0;
}

