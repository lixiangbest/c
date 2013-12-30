/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *
 *    Description:  fifo client program.
 *
 *        Version:  1.0
 *        Created:  06/10/13 15:22:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<fcntl.h>
#include<ctype.h>
#include<limits.h>

#define SERVER_FIFO_NAME "./server__fifo"
#define CLIENT_FIFO_NAME "./client_%d_fifo"

#define BUFFER_SIZE PIPE_BUF
#define MESSAGE_SIZE 20
#define NAME_SIZE 256

typedef struct message{
	pid_t client_pid;
	char data[MESSAGE_SIZE+1];
}message;

int main(){
	int server_fifo_fd;
	int client_fifo_fd;
	int res;
	char client_fifo_name[NAME_SIZE];

	message msg;

	msg.client_pid = getpid();
	sprintf(client_fifo_name, CLIENT_FIFO_NAME, msg.client_pid);
	
	/*make server fifo file.*/
	if(mkfifo(client_fifo_name, 0777) == -1){
		err_sys("Sorry, create server fifo failure.");
	}

	if((server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY)) == -1)
		err_sys("Sorry, server fifo open failure.");
	
	sprintf(msg.data, "Hello from %d", msg.client_pid);
	printf("%d sent %s ", msg.client_pid, msg.data);
	if(write(server_fifo_fd, &msg, sizeof(msg))<0)
		err_sys("Wrtie to server fifo %s error.", client_fifo_name);

	/*open client_fifo file.*/
	if((client_fifo_fd = open(client_fifo_name, O_RDONLY)) == -1)
		err_sys("Sorry, client fifo open failure.");
	if((res = read(client_fifo_fd, &msg, sizeof(msg))) > 0)
		printf("%d received:%s\n", msg.client_pid, msg.data);

	close(client_fifo_fd);
	close(server_fifo_fd);
	unlink(client_fifo_name);
	exit(0);	
}
