/*************************************************************************
	> File Name: 15/unixstrcli01.c
	> Description: 
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月14日 星期六 08时58分38秒
 ************************************************************************/
#include "unp.h"

int main(int argc, char **argv){
	int sockfd;
	struct sockaddr_un servaddr;

	sockfd = Socket(AF_LOCAL, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UNIXSTR_PATH);
	
	Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));

	str_cli(stdin, sockfd);/*do it all*/
	
	exit(0);
}
