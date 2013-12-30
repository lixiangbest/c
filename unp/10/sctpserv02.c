/*
 * =====================================================================================
 *
 *       Filename:  sctpserv02.c
 *
 *    Description:  sctp server.
 *
 *        Version:  1.0
 *        Created:  11/10/13 23:18:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

sctp_assoc_t sctp_address_to_associd(int sock_fd, struct sockaddr *sa, socklen_t salen){
	struct sctp_paddrparams sp;
	int siz;

	siz = sizeof(struct sctp_paddrparams);
	bzero(&sp, siz);
	memcpy(&sp.spp_address, sa, salen);
	sctp_opt_info(sock_fd, 0, SCTP_PEER_ADDR_PARAMS, &sp, (socklen_t *)&siz);

	return(sp.spp_assoc_id);
}

int sctp_get_no_strms(int sock_fd, struct sockaddr *to, socklen_t tolen){
	int retsz;
	struct sctp_status status;
	retsz = sizeof(status);
	bzero(&status, sizeof(status));

	status.sstat_assoc_id = sctp_address_to_associd(sock_fd, to, tolen);
	getsockopt(sock_fd, IPPROTO_SCTP, SCTP_STATUS, &status, (socklen_t *)&retsz);

	return(status.sstat_outstrms);
}

int main(int argc, char **argv){
	int sock_fd, msg_flags;
	char readbuf[BUFFSIZE];
	struct sockaddr_in servaddr, cliaddr;
	struct sctp_sndrcvinfo sri;
	struct sctp_event_subscribe evnts;
	
	int stream_increment = 1;
	socklen_t len;
	size_t rd_sz;
	struct sctp_initmsg initm;

	if(argc == 2)
		stream_increment = atoi(argv[1]);
	sock_fd = Socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);

	/*include modified_sctpserv02*/
	bzero(&initm, sizeof(initm));
	initm.sinit_num_ostreams = SERV_MORE_STRMS_SCTP;
	Setsockopt(sock_fd, IPPROTO_SCTP, SCTP_INITMSG, &initm, sizeof(initm));
	/*end modified_sctpserv02*/

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(sock_fd, (SA*)&servaddr, sizeof(servaddr));

	bzero(&evnts, sizeof(evnts));
	evnts.sctp_data_io_event = 1;
	Setsockopt(sock_fd, IPPROTO_SCTP, SCTP_EVENTS, &evnts, sizeof(evnts));

	Listen(sock_fd, LISTENQ);
	for(;;){
		len = sizeof(struct sockaddr_in);
		rd_sz = sctp_recvmsg(sock_fd, readbuf, sizeof(readbuf), (SA*)&cliaddr, &len, &sri, &msg_flags);
		if(stream_increment){
			sri.sinfo_stream++;
			/*printf("sri.sinfo_stream:%d\n", sri.sinfo_stream);*/
			if(sri.sinfo_stream >= sctp_get_no_strms(sock_fd, (SA*)&cliaddr, len))
				sri.sinfo_stream = 0;
		}
		/*sctp_sendmsg(sock_fd, readbuf, rd_sz, (SA*)&cliaddr, len, sri.sinfo_ppid, sri.sinfo_flags, sri.sinfo_stream, 0, 0);*/
		sctp_sendmsg(sock_fd, readbuf, rd_sz, (SA*)&cliaddr, len, sri.sinfo_ppid, sri.sinfo_flags, sri.sinfo_stream, 0, 0);
	}

	return 0;
}

