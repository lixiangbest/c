/*************************************************************************
	> File Name: getrt.c
	> Description: get route according to the gived IPv4.
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月25日 星期三 00时22分37秒
 ************************************************************************/
#include "unproute.h"
struct route_info{
	u_int dstaddr;
	u_int srcaddr;
	u_int gateway;
	char ifname[IF_NAMESIZE];
};

int readnlsock(int sockfd, char *bufptr, int seqnum, int pid){
	struct nlmsghdr *nlhdr;
	int readlen = 0, msglen = 0;
	do{
		//receive the kernel response.
		if( (readlen = recv(sockfd, bufptr, BUFSIZ - msglen, 0)) < 0 ){
			perror("SOCK READ: ");
			return -1;
		}
		//printf("readlen:%d\n", readlen);

		nlhdr = (struct nlmsghdr *)bufptr;
		//check the header.
		if( (NLMSG_OK(nlhdr, readlen) == 0) || (nlhdr->nlmsg_type == NLMSG_ERROR) ){
			perror("Error in received packet.");
			return -1;
		}

		if(nlhdr->nlmsg_type == NLMSG_DONE)
			break;
		else{
			bufptr += readlen;
			msglen += readlen;
		}

		if( (nlhdr->nlmsg_flags & NLM_F_MULTI) == 0 )
			break;
	}while( (nlhdr->nlmsg_seq != seqnum) || (nlhdr->nlmsg_pid != pid) );
	return msglen;
}

//parse routes
void parseroutes(struct nlmsghdr *nlhdr, struct route_info *rinfo, char *gateway){
	struct rtmsg *rmsg;
	struct rtattr *rattr;
	int rlen;
	char *tempbuf = NULL;
	struct in_addr dst;
	struct in_addr gate;

	tempbuf = (char *)malloc(100);
	rmsg = (struct rtmsg *)NLMSG_DATA(nlhdr);
	
	//if the route is not for AF_INET or does not belong to main routing table
	//then return.
	if( (rmsg->rtm_family != AF_INET) || (rmsg->rtm_table != RT_TABLE_MAIN) )
		return;

	rattr = (struct rtattr*)RTM_RTA(rmsg);
	rlen = RTM_PAYLOAD(nlhdr);
	for(;RTA_OK(rattr, rlen);rattr = RTA_NEXT(rattr, rlen)){
		switch(rattr->rta_type){
			case RTA_OIF:
				if_indextoname( *(int *)RTA_DATA(rattr), rinfo->ifname );
				//printf("ifname:%s\n", rinfo->ifname);
				break;
			case RTA_GATEWAY:
				rinfo->gateway = *(u_int *)RTA_DATA(rattr);
				break;
			case RTA_PREFSRC:
				rinfo->srcaddr = *(u_int *)RTA_DATA(rattr);
				break;
			case RTA_DST:
				rinfo->dstaddr = *(u_int *)RTA_DATA(rattr);
				break;
		}
	}
	dst.s_addr = rinfo->dstaddr;
	//printf("dstaddr:0x%x\n", rinfo->dstaddr);
	//if(strstr( (char*)inet_ntoa(dst), "0.0.0.0" )){
		printf("Iface:%s\n", rinfo->ifname);
		gate.s_addr = rinfo->dstaddr;
		printf("Destination:%s\n", (char *)inet_ntoa(gate));

		gate.s_addr = rinfo->gateway;
		printf("Gateway:%s\n", (char *)inet_ntoa(gate));

		gate.s_addr = rinfo->srcaddr;
		printf("Src:%s\n\n", (char *)inet_ntoa(gate));
	//}
	free(tempbuf);
	return;
}

/*get gateway*/
int get_gateway(char *gateway){
	struct nlmsghdr *nlmsg;
	struct rtmsg *rtmsg;
	struct route_info *rtinfo;
	char msgbuf[BUFSIZ];
	int sock, len, msgseq = 0;

	sock = Socket(PF_NETLINK, SOCK_DGRAM, NETLINK_ROUTE);

	memset(msgbuf, 0, BUFSIZ);

	nlmsg = (struct nlmsghdr *)msgbuf;
	rtmsg = (struct rtmsg *)NLMSG_DATA(nlmsg);

	nlmsg->nlmsg_len = NLMSG_LENGTH(sizeof(struct rtmsg));//Length of message.
	nlmsg->nlmsg_type = RTM_GETROUTE;//Get the routes from kernel routing table.
	nlmsg->nlmsg_flags = NLM_F_DUMP | NLM_F_REQUEST;//The message is a request for dump
	nlmsg->nlmsg_seq = msgseq++;//sequence of the message packet.
	nlmsg->nlmsg_pid = getpid();//pid of process sending the request.
	
	Send(sock, nlmsg, nlmsg->nlmsg_len, 0);
	
	//our defined function.
	if( (len = readnlsock(sock, msgbuf, msgseq, getpid())) < 0 ){
		err_quit("Read from socket failed...\n");
	}
	//printf("len:%d\n", len);
	rtinfo = (struct route_info *)malloc(sizeof(struct route_info));
	for(;NLMSG_OK(nlmsg, len);nlmsg=NLMSG_NEXT(nlmsg, len)){
		memset(rtinfo, 0, sizeof(struct route_info));
		//our defined function.
		parseroutes(nlmsg, rtinfo, gateway);
	}
	free(rtinfo);
	close(sock);
	return 0;
}

int main(){
	char gateway[256];
	get_gateway(gateway);
	printf("IF_NAMESIZE:%d, gateway:%s\n", IF_NAMESIZE, gateway);
	return 0;
}

