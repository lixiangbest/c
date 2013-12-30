/*
 * =====================================================================================
 *
 *       Filename:  usock_client.c
 *
 *    Description:  unix socket client.
 *
 *        Version:  1.0
 *        Created:  06/30/13 17:34:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<sys/un.h>
#include<sys/types.h>
#include<sys/socket.h>

#define MAX_SEND 1024
#define UNIX_PATH "/home/suncco/c/apue/17/u.sock"

void dump_unix(int sock_fd){
	char tmp[MAX_SEND] = {0};
	char recv[MAX_SEND] = {0};
	while(fgets(tmp, MAX_SEND, stdin) != NULL){
		write(sock_fd, tmp, strlen(tmp));
		read(sock_fd, recv, MAX_SEND);
		printf("data: %s\n", recv);
		bzero(tmp, MAX_SEND);
		bzero(recv, MAX_SEND); 
	}
}

int main(int argc, char **argv){
	int conn_sock;
	struct sockaddr_un addr;
	if((conn_sock = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0){
		err_sys("create unix socket fail");
	}

	bzero(&addr, sizeof(addr));
	addr.sun_family = AF_LOCAL;
	strcpy((void*)&addr.sun_path, UNIX_PATH);
	if(connect(conn_sock, (struct sockaddr*)&addr, sizeof(addr)) < 0){
		err_sys("connect socket error");
	}
	dump_unix(conn_sock);
	close(conn_sock);
	return 0;
}

