/*************************************************************************
	> File Name: mycat.c
	> Description: 
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月16日 星期一 05时41分08秒
 ************************************************************************/
#include "unp.h"

int my_open(const char *, int);

int main(int argc, char **argv){
	int fd, n;
	char buff[BUFFSIZE];

	if(argc != 2){
		err_quit("usage: mycat <pathname>");
	}

	if( (fd = my_open(argv[1], O_RDONLY)) < 0)
		err_sys("cannot open %s", argv[1]);

	while( (n = Read(fd, buff, BUFFSIZE)) > 0){
		Write(STDOUT_FILENO, buff, n);
	}
	exit(0);
}

int my_open(const char *pathname, int mode){
	int fd, sockfd[2], status, count;
	pid_t childpid;
	char c, argsockfd[10], argmode[10];

	Socketpair(AF_LOCAL, SOCK_STREAM, 0, sockfd);

	if( (childpid = Fork())==0){/*child process*/
		Close(sockfd[0]);
		snprintf(argsockfd, sizeof(argsockfd), "%d", sockfd[1]);
		snprintf(argmode, sizeof(argmode), "%d", mode);
		execl("./openfile", "openfile", argsockfd, pathname, argmode, (char *)NULL);
		err_sys("execl error");
	}

	/* parent process - wait for the child to terminate*/
	Close(sockfd[1]);/*close the end we don't use*/

	Waitpid(childpid, &status , 0);
	if(WIFEXITED(status)==0)
		err_quit("child did not terminate");
	if( (status = WEXITSTATUS(status))==0){
		count = Read_fd(sockfd[0], &c, 1, &fd);
		printf("char:%c,recvfd:%d,read count:%d\n", c, fd, count);
	}else{
		errno = status;/*set errno value from child's status*/
		fd = -1;
	}

	Close(sockfd[0]);
	return fd;
}
