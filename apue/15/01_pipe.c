/*
 * =====================================================================================
 *
 *       Filename:  01_pipe.c
 *
 *    Description:  pipe
 *
 *        Version:  1.0
 *        Created:  06/02/13 18:46:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<sys/wait.h>

static void sig_pipe(int signo){
	printf("catch SIGPIPE:%d\n",signo);
}

int main(void){
	int n;
	int fd[2];
	struct stat sbuf;
	pid_t pid;
	char line[MAXLINE];

	if(signal(SIGPIPE, sig_pipe) < 0){
		err_sys("sig_pipe error!");
	}
	if(pipe(fd) < 0){
		err_sys("pipe error!");
	}
	/*test the pipe fd*/
	if(fstat(fd[0],&sbuf)<0){
		err_sys("fstat error!");
	}else{
		printf("is_pipe:0%o,%d\n",sbuf.st_mode,S_ISFIFO(sbuf.st_mode));
	}

	TELL_WAIT();
	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid > 0){/*parent*/
		close(fd[0]);/*Close parent read fd*/
		/*close(fd[1]);*//*Close parent write fd*/
		/*sleep(1);*//*wait until child is end.*/
		WAIT_CHILD();/*wait for child*/

		if((n = write(fd[1], "hello world\n", 12)) < 0){
			/*err_sys("write error");*/
			perror("write error");
		}
		printf("parent write:%d\n", n);

		if(waitpid(pid, NULL, 0)<0){
			err_sys("wait child :%d error", (int)pid);
		}
		printf("wait success!\n");
	}else{
		close(fd[1]);/*close child write fd*/
		close(fd[0]);/*close child read fd*/
		TELL_PARENT(getppid());/*Tell parent.*/

		if((n = read(fd[0], line, MAXLINE)) < 0){
			err_sys("read error");
		}
		printf("child read:%d\n", n);
		write(STDOUT_FILENO, line, n);
	}
	exit(0);
}
