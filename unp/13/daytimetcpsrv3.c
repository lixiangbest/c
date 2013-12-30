/*************************************************************************
	> File Name: daytimetcpsrv3.c
	> Descript: mydaytime service started by inetd/xinetd
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月02日 星期一 03时40分54秒
 ************************************************************************/
#include "unp.h"
#include<time.h>

int main(int argc, char **argv){
	socklen_t len;
	struct sockaddr *cliaddr;
	char buff[MAXLINE];
	time_t ticks;

	daemon_inetd(argv[0], 0);

	len = sizeof(struct sockaddr_storage);
	cliaddr = Malloc(len);
	Getpeername(0, cliaddr, &len);/*notice the socket descriptor is 0.*/
	err_msg("connection from %s", Sock_ntop(cliaddr, len));

	ticks = time(NULL);
	snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
	Write(0, buff, strlen(buff));
	
	Close(0);/*close TCP connection*/
	exit(0);
}
