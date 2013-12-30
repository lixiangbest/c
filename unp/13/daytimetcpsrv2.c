/*************************************************************************
	> File Name: daytimetcpsrv2.c
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月01日 星期日 13时01分47秒
 ************************************************************************/
#include "unp.h"
#include<time.h>
#include<syslog.h>

int main(int argc, char **argv){
	int listenfd, connfd;
	socklen_t addrlen, len;
	struct sockaddr *cliaddr;
	char buff[MAXLINE];
	time_t ticks;

	if(argc < 2 || argc > 3)
		err_quit("usage: daytimetcpsrv2 [ <host> ] <service or port>");

	daemon_init(argv[0], 0);

	if(argc == 2)
		listenfd = Tcp_listen(NULL, argv[1], &addrlen);
	else
		listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
	
	/*syslog(LOG_INFO|LOG_LOCAL2, "listenfd:%d\n", listenfd);*/

	cliaddr = Malloc(addrlen);
	
	for(;;){
		len = addrlen;
		connfd = Accept(listenfd, cliaddr, &len);
		err_msg("connection from %s", Sock_ntop(cliaddr, len));

		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		Write(connfd, buff, strlen(buff));

		Close(connfd);
	}
}
