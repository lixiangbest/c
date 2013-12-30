/*
 * =====================================================================================
 *
 *       Filename:  sctpdaycli.c
 *
 *    Description:  sctp day client.
 *
 *        Version:  1.0
 *        Created:  11/11/13 22:14:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

int main(int argc, char *argv[]){
	int connSock, in, i, flags;
	struct sockaddr_in servaddr;
	struct sctp_sndrcvinfo sndrcvinfo;
	struct sctp_event_subscribe events;
	char buffer[MAXLINE+1];

	if(argc < 2)
		err_quit("Missing host argument - use '%s host [echo]'\n", argv[0]);

	/* Create SCTP TCP-Style Socket*/
	connSock = Socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);

	/* Specify the peer endpoint to which we'll connect */
	bzero( (void*)&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	/*servaddr.sin_addr.s_addr = htonl(INADDR_ANY);*/
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	servaddr.sin_port = htons(SERV_PORT);
	
	/* Connect to the server */
	connect( connSock, (struct sockaddr *)&servaddr, sizeof(servaddr) );
	
	/* Enable receipt of SCTP Snd/Rcv Data via sctp_recvmsg */
	memset( (void *)&events, 0, sizeof(events) );
	events.sctp_data_io_event = 1;
	setsockopt( connSock, SOL_SCTP, SCTP_EVENTS, (const void *)&events, sizeof(events) );
	
	/* Expect two messages from the peer */
	for(i = 0; i < 2; i++){
		in = sctp_recvmsg( connSock, (void *)buffer, sizeof(buffer), (struct sockaddr *)NULL, 0, &sndrcvinfo, &flags);
		/* Null terminate the incoming string */
		buffer[in] = 0;
		if(sndrcvinfo.sinfo_stream == 0){
			printf("(Local) %s\n", buffer);
		}else if(sndrcvinfo.sinfo_stream == 1){
			printf("(GMT ) %s\n", buffer);
		}
	}
	/* Close our socket and exit */
	close(connSock);
	return 0;
}

