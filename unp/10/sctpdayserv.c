/*
 * =====================================================================================
 *
 *       Filename:  sctpdayserv.c
 *
 *    Description:  sctp day query server.
 *
 *        Version:  1.0
 *        Created:  11/11/13 21:54:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

int main(){
	int listenSock, connSock, ret;
	struct sockaddr_in servaddr;
	char buffer[MAXLINE+1];
	time_t currentTime;

	/* Create SCTP TCP-Style Socket*/
	listenSock = Socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);

	/* Accept connections from any interface */
	bzero( (void*)&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	/* Bind to the wildcard address (all) and SERV_PORT */
	ret = bind(listenSock, (struct sockaddr *)&servaddr, sizeof(servaddr));
	/* Place the server socket into the listening state*/
	listen(listenSock, LISTENQ);
	/* Server loop...*/
	while(1){
		/* Await a new client connection */
		connSock = accept(listenSock, (struct sockaddr *)NULL, (socklen_t *)NULL);
		/* New client socket has connected */
		/* Grab the current time */
		currentTime = time(NULL);
		/* Send local time on stream 0 (local time stream) */
		snprintf(buffer, MAXLINE, "%s\n", ctime(&currentTime) );
		/*printf("buffer = %s\n", buffer);*/
		ret = sctp_sendmsg(connSock, (void*)buffer, (size_t)strlen(buffer), NULL, 0, 0, 0, 0, 0, 0);

		/* Send GMT on stream 1 (GMT stream) */
		snprintf(buffer, MAXLINE, "%s\n", asctime( gmtime(&currentTime) ) );
		/*printf("buffer = %s\n", buffer);*/
		ret = sctp_sendmsg(connSock, (void*)buffer, (size_t)strlen(buffer), NULL, 0, 0, 0, 1, 0, 0);

		/* Close the client connection */
		close(connSock);
	}

	return 0;
}

