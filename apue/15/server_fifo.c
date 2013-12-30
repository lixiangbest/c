/*
 * =====================================================================================
 *
 *       Filename:  server_fifo.c
 *
 *    Description:  product, write data to fifo.
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
	int open_mode = O_WRONLY;
	int bytes = 0;
	char buffer[BUFFER_SIZE+1];

	/*check the write-read authority, whether file is exist.*/
	if(access(FIFO_NAME, F_OK) == -1){
		res = mkfifo(FIFO_NAME, 0777);
		if(res!=0){
			/*fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME;*/
			err_sys("Could not create fifo %s\n", FIFO_NAME);
		}
	}

	printf("Process %d opening FIFO O_WRONLY\n", getpid());
	pipe_fd = open(FIFO_NAME, open_mode);/*block on open function.*/
	printf("Process %d result %d\n", getpid(), pipe_fd);

	if(pipe_fd != -1){
		while(bytes < TEN_MEG){
			res = write(pipe_fd, buffer, BUFFER_SIZE);
			if(res == -1){
				/*fprintf(stderr, "Write error on pipe\n");*/
				err_sys("Write error on pipe");
			}
			bytes += res;
		}
		close(pipe_fd);
	}else{
		err_sys("open error on pipe");
	}

	printf("Process %d finish, %d bytes write\n", getpid(), bytes);
	printf("EXIT_SUCCESS:%d,EXIT_FAILURE:%d\n", EXIT_SUCCESS, EXIT_FAILURE);
	exit(0);
}
