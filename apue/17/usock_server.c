/*
 * =====================================================================================
 *
 *       Filename:  usock_server.c
 *
 *    Description:  unix socket server.
 *
 *        Version:  1.0
 *        Created:  06/30/13 17:34:39
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
#include<sys/wait.h>

#define MAX_RECV 1024
#define UNIX_SERV_PATH "/home/suncco/c/apue/17/u.sock"

void sig_son(int num){
	pid_t cid;
	if((cid = wait(NULL)) > 0)
		printf("son is %d\n", cid);
}

void sig_intr(int signo){
	printf("catch sigint\n");
	unlink(UNIX_SERV_PATH);/*unlink for the next usage*/
	exit(0);
}

void client_dump(int sock_fd){
	char rec[MAX_RECV] = {0};
	int size;
	while((size = read(sock_fd, rec, MAX_RECV)) > 0){
		printf("****************************\n");
		printf("recv data is %s\n", rec);
		write(sock_fd, rec, size);
		bzero(rec, MAX_RECV);/*you must empty rec*/
	}
}

int main(int argc, char **argv){
	int acc_sock, dump_sock;
	struct sockaddr_un ser_addr, cli_addr;

	if((acc_sock = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0)
		err_sys("socket func fail");
	
	printf("acc_sock:%d\n",acc_sock);
	ser_addr.sun_family = AF_LOCAL;
	strcpy(ser_addr.sun_path, UNIX_SERV_PATH);
	printf("path:%s\n", ser_addr.sun_path);
	unlink(UNIX_SERV_PATH);/*unlink for the next usage*/
	
	if(bind(acc_sock, (struct sockaddr*)&ser_addr, sizeof(ser_addr)) < 0)
		err_sys("bind %s error", UNIX_SERV_PATH);
	if(listen(acc_sock, 5) < 0)
		err_sys("listen error");
	signal(SIGCHLD, sig_son);
	signal(SIGINT, sig_intr);
	while(1){
		int len = sizeof(cli_addr);
		if((dump_sock = accept(acc_sock, (struct sockaddr*)&cli_addr, (socklen_t *)&len)) < 0){
			err_sys("accept error");
		}
		if(fork() == 0){/*child*/
			close(acc_sock);
			client_dump(dump_sock);
			close(dump_sock);
			exit(0);
		}
		close(dump_sock);
	}
	close(acc_sock);
	return 0;
}
