/*
 * =====================================================================================
 *
 *       Filename:  client_fifo.c
 *
 *    Description:  consumer, read data from fifo.
 *
 *        Version:  1.0
 *        Created:  06/08/13 05:19:13
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
#include<limits.h>

#define FIFO_NAME "./my_fifo"
#define BUFFER_SIZE PIPE_BUF
#define TEN_MEG (1024*1024*10)

int main(){
	int pipe_fd;
	int res;
	int open_mode = O_RDONLY;
	int bytes = 0;
	char buffer[BUFFER_SIZE+1];

	memset(buffer, '\0', sizeof(buffer));

	printf("Process %d opening FIFO O_WRONLY\n", getpid());
	pipe_fd = open(FIFO_NAME, open_mode);/*block on open function.*/
	printf("Process %d result %d\n", getpid(), pipe_fd);

	if(pipe_fd != -1){
		do{
			res = read(pipe_fd, buffer, BUFFER_SIZE);
			bytes += res;
			/*
			if(write(STDOUT_FILENO, buffer, res)<0){
				err_sys("error read");
			}
			*/
		}while(res > 0);
		close(pipe_fd);
	}else{
		err_sys("open error on pipe");
	}

	printf("Process %d finish, %d bytes read\n", getpid(), bytes);
	printf("EXIT_SUCCESS:%d,EXIT_FAILURE:%d\n", EXIT_SUCCESS, EXIT_FAILURE);
	exit(0);
}
