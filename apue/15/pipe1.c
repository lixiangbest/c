/*
 * =====================================================================================
 *
 *       Filename:  pipe1.c
 *
 *    Description:  pipe block.
 *
 *        Version:  1.0
 *        Created:  06/02/13 22:32:43
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
#include<fcntl.h>

int main(void){
	int n;
	int fd[2];
	pid_t pid;
	char line[MAXLINE];

	if(pipe(fd) < 0){
		err_sys("pipe error!");
	}

	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){/*child*/
		close(fd[0]);/*Close child read fd*/
		sleep(5);
		if((n = write(fd[1], "hello world\n", 12)) < 0){
			/*err_sys("write error");*/
			perror("write error");
		}
		printf("child write:%d\n", n);

	}else{
		close(fd[1]);/*close child write fd*/
		
		printf("parent read will block\n");
		/*set_fl(fd[0], O_NONBLOCK);*//*set read fd unblock*/
		if((n = read(fd[0], line, MAXLINE)) < 0){
			err_sys("read error");
		}
		printf("parent read:%d\n", n);
		write(STDOUT_FILENO, line, n);
		if(waitpid(pid, NULL, 0)<0){
			err_sys("wait child :%d error", (int)pid);
		}
		printf("wait success!\n");
	}
	exit(0);
}
