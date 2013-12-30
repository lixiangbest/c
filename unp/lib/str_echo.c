/*
 * =====================================================================================
 *
 *       Filename:  str_echo.c
 *
 *    Description:  str echo for tcpserv01.c
 *
 *        Version:  1.0
 *        Created:  07/15/13 21:41:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

void str_echo(int sockfd){
	ssize_t n;
	char buf[MAXLINE];

again:
	while( (n = read(sockfd, buf, MAXLINE)) > 0)
		Writen(sockfd, buf, n);

	if(n < 0 && errno == EINTR)
		goto again;
	else if(n < 0)
		err_sys("str_echo: read error");
}

