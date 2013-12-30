/*
 * =====================================================================================
 *
 *       Filename:  openclient.c
 *
 *    Description:  client open fd from server.
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
		printf("connect socket open fd:%d\n", fd);
		/*read the fd current offset.*/
		printf("current offset:%d\n\n", lseek(fd, 0, SEEK_CUR));
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
	pid_t pid;
	int len;
	char buf[10];
	struct iovec iov[3];
	static int fd[2] = {-1, -1};

	if(fd[0] < 0){/*fork/exec our open server first time*/
		/*socketpair function.pass fd with address.It's two way communication.*/
		if(s_pipe(fd) < 0){
			err_sys("s_pipe error");
		}
		printf("fd[0]:%d, fd[1]:%d\n", fd[0], fd[1]);

		if((pid = fork()) < 0){
			err_sys("fork error");
		}else if(pid == 0){/*child*/
			close(fd[1]);
			
			if(fd[0] != STDIN_FILENO && dup2(fd[0], STDIN_FILENO) != STDIN_FILENO){
				err_sys("dup2 error to stdin");
			}
			
			if(fd[0] != STDOUT_FILENO && dup2(fd[0], STDOUT_FILENO) != STDOUT_FILENO){
				err_sys("dup2 error to stdout");
			}
			
			if(execl("./opend", "opend", (char *)0) < 0)
				err_sys("execl error");
		}
		close(fd[0]);/*parent*/
	}
	sprintf(buf, " %d", oflag);/*oflag to ascii*/
	iov[0].iov_base = CL_OPEN " ";/*string concatenation*/
	iov[0].iov_len = strlen(CL_OPEN) + 1;
	iov[1].iov_base = name;
	iov[1].iov_len = strlen(name);
	iov[2].iov_base = buf;
	iov[2].iov_len = strlen(buf) + 1;/*+1 for null at end of buf*/
	len = iov[0].iov_len + iov[1].iov_len + iov[2].iov_len;
	printf("write iov[%d]:%s, iov[%d]:%s, iov[%d]:%s\n\n", 0, (char *)iov[0].iov_base,1, (char *)iov[1].iov_base, 2, (char *)iov[2].iov_base);
	if(writev(fd[1], &iov[0], 3) != len){
		err_sys("writeev error");
	}

	/*read descriptor, returned errors handled by write()*/
	return(recv_fd(fd[1], write));
}
