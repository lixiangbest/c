/*
 * =====================================================================================
 *
 *       Filename:  11_fifo.c
 *
 *    Description:  FIFO
 *
 *        Version:  1.0
 *        Created:  06/08/13 01:35:33
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

#define FIFO "temp.fifo"

int main(void){
	int fdread, fdwrite, n;
	char buf[MAXLINE];
	pid_t pid;
	if(unlink(FIFO) < 0){
		err_msg("unlink %s error", FIFO);
	}
	if(mkfifo(FIFO, FILE_MODE) < 0)
		err_sys("mkfifo error");
	/*if((fdread = open(FIFO, O_RDONLY|O_NONBLOCK)) < 0)*/
	if((fdread = open(FIFO, O_RDONLY)) < 0)
		err_sys("open error for reading");
	if((fdwrite = open(FIFO, O_WRONLY)) < 0)
		err_sys("open error for writing");
	/*clr_fl(fdread, O_NONBLOCK);*/

	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid>0){/*parent*/
		while(fgets(buf, MAXLINE, stdin) != NULL){
			n = strlen(buf);
			/*write to FIFO*/
			if(write(fdwrite, buf, n) != n)
				err_sys("write error to FIFO");
		}
	}else{
		/*read from FIFO*/
		while((n = read(fdread, buf, MAXLINE) < 0)){
			/*err_sys("read error from FIFO");*/
			buf[n] = 0;/*null terminate*/
			if(fputs(buf, stdout) == EOF)
				err_sys("fputs error");
			printf("n=%d\n", n);
		}
	}
	if(ferror(stdin))
		err_sys("fgets error on stdin");
	exit(0);
}
