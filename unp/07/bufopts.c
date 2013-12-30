/*
 * =====================================================================================
 *
 *       Filename:  bufopts.c
 *
 *    Description:  tcp and udp send and receive buf.
 *
 *        Version:  1.0
 *        Created:  10/28/13 23:16:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

int main(void){
	int sndbuf, rcvbuf, tcpfd, udpfd;
	socklen_t sndlen = sizeof(sndbuf);
	socklen_t rcvlen = sizeof(rcvbuf);

	tcpfd = Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);/*tcp*/
	if(getsockopt(tcpfd, SOL_SOCKET, SO_SNDBUF, (void*)&sndbuf, &sndlen) < 0){
		err_sys("get tcp sndbuf error!\n");
	}else{
		printf("tcp sndbuf:%d\n", sndbuf);
	}
	if(getsockopt(tcpfd, SOL_SOCKET, SO_RCVBUF, (void*)&rcvbuf, &rcvlen) < 0){
		err_sys("get tcp rcvbuf error!\n");
	}else{
		printf("tcp rcvbuf:%d\n", rcvbuf);
	}

	udpfd = Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);/*udp*/
	if(getsockopt(udpfd, SOL_SOCKET, SO_SNDBUF, (void*)&sndbuf, &sndlen) < 0){
		err_sys("get udp sndbuf error!\n");
	}else{
		printf("udp sndbuf:%d\n", sndbuf);
	}
	if(getsockopt(udpfd, SOL_SOCKET, SO_RCVBUF, (void*)&rcvbuf, &rcvlen) < 0){
		err_sys("get udp sndbuf error!\n");
	}else{
		printf("udp rcvbuf:%d\n", rcvbuf);
	}

	return 0;
}

