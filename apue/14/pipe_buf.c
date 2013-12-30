/*
 * =====================================================================================
 *
 *       Filename:  pipe_buf.c
 *
 *    Description:  pipe buf
 *
 *        Version:  1.0
 *        Created:  06/01/13 21:59:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<limits.h>
#include<fcntl.h>

int main(void){
	int i, n;
	int fd[2];
	
	printf("PIPE_BUF = %d\n", PIPE_BUF);
	if(pipe(fd) < 0){
		err_sys("pipe error");
	}
	set_fl(fd[1], O_NONBLOCK);/*pipe fd[0] read;fd[1] write.*/
	
	/*
	 * Write 1 byte at a time until pipe is full.
	 */
	for(n=0; ; n++){
		/*write 'a' to fd read.when block and buf full, write will be block*/
		if((i = write(fd[1], "a", 1)) != 1){
			printf("write ret %d, ", i);
			break;
		}
		/*else printf("wirte i=%d\n", i);*/
	}
	printf("pipe capacity = %d\n", n);
	return 0;
}

