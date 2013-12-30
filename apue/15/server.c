/*
 * =====================================================================================
 *
 *       Filename:  server.c
 *
 *    Description:  fifo server program.
 *
 *        Version:  1.0
 *        Created:  06/10/13 14:55:17
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
	char *p;
	
	/*make server fifo file.*/
	if(mkfifo(SERVER_FIFO_NAME, 0777) == -1){
		err_sys("Sorry, create server fifo failure.");
	}

	if((server_fifo_fd = open(SERVER_FIFO_NAME, O_RDONLY)) == -1)
		err_sys("Sorry, server fifo open failure.");
	
	printf("you will see server block in open fifo until the client open the same fifo.\n");
	sleep(5);
	while((res = read(server_fifo_fd, &msg, sizeof(msg))) > 0){
		p = msg.data;
		/*lower case to upper case.*/
		while(*p){
			*p = toupper(*p);
			p++;
		}

		sprintf(client_fifo_name, CLIENT_FIFO_NAME, msg.client_pid);
		if((client_fifo_fd = open(client_fifo_name, O_WRONLY)) == -1)
			err_sys("Sorry, client fifo open failure.");

		if(write(client_fifo_fd, &msg, sizeof(msg))<0){
			err_sys("Wrtie to client fifo %s error.", client_fifo_name);
		}
		close(client_fifo_fd);
	}
	close(server_fifo_fd);
	unlink(SERVER_FIFO_NAME);
	exit(0);
}
