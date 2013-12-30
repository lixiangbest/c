/*
 * =====================================================================================
 *
 *       Filename:  open_dae.c
 *
 *    Description:  client open fd from daemon server.
 *
 *        Version:  1.0
 *        Created:  06/15/13 15:56:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
/*start open.h*/
#include "apue.h"
#include<errno.h>

#define CL_OPEN "open" /*client's request for server*/
#define CS_OPEN "/home/suncco/c/apue/17/opend_dae.so" /*server's well-known name*/

int csopen(char *, int);
/*end open.h*/

#include<fcntl.h>
#include<sys/uio.h>/*struct iovec*/

#define BUFFSIZE 8192

int main(int argc, char *argv[]){
	int n, fd;
	char buf[BUFFSIZE], line[MAXLINE];

	printf("parentid:%d\n", getpid());
	/*read filename to cat from stdin*/
	while(fgets(line, MAXLINE, stdin) != NULL){
		/*replace newline with null*/
		if(line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = 0;/*replace newline with null*/

		/*open the file*/
		if((fd = csopen(line, O_RDONLY)) < 0)
			continue;/*csopen() prints error from server*/
		printf("connect socket open fd:%d\n\n", fd);
		/*and cat to stdout*/
		while((n = read(fd, buf, BUFFSIZE)) > 0)
			if(write(STDOUT_FILENO, buf, n) != n)
				err_sys("write error");
		if(n < 0)
			err_sys("read error");
		close(fd);
	}
	
	exit(0);
}

/*
 * Open the file by sending the "name" and "oflag" to the
 * connection server and reading a file descriptor back.
 */
int csopen(char *name, int oflag){
	int len;
	char buf[10];
	struct iovec iov[3];
	static int csfd = -1;

	if(csfd < 0){/*open connection to conn server*/
		if((csfd = cli_conn(CS_OPEN)) < 0)
			err_sys("cli_conn error");
	}

	sprintf(buf, " %d", oflag);/*oflag to ascii*/
	iov[0].iov_base = CL_OPEN " ";/*string concatenation*/
	iov[0].iov_len = strlen(CL_OPEN) + 1;
	iov[1].iov_base = name;
	iov[1].iov_len = strlen(name);
	iov[2].iov_base = buf;
	iov[2].iov_len = strlen(buf) + 1;/*null always sent*/
	len = iov[0].iov_len + iov[1].iov_len + iov[2].iov_len;
	printf("write iov[%d]:%s, iov[%d]:%s, iov[%d]:%s\n\n", 0, (char *)iov[0].iov_base,1, (char *)iov[1].iov_base, 2, (char *)iov[2].iov_base);
	if(writev(csfd, &iov[0], 3) != len){
		err_sys("writeev error");
	}

	/*read descriptor, returned errors handled by write()*/
	return(recv_fd(csfd, write));
}
