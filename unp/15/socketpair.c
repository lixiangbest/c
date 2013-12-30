/*************************************************************************
	> File Name: socketpair.c
	> Description: socketpair communication.
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月17日 星期二 23时26分53秒
 ************************************************************************/
#include "unp.h"

int main(){
	int fd[2];
	int r = socketpair(AF_UNIX, SOCK_STREAM, 0, fd);
	if( r < 0 ){
		err_quit("socketpair error");
	}
	if( fork() ){
		/*parent process: echo client*/
		int val = 0;
		close(fd[1]);
		while(1){
			sleep(1);
			++val;
			printf("parent sending data: %d\n", val);
			write(fd[0], &val, sizeof(val));
			read(fd[0], &val, sizeof(val));
			printf("parent data received: %d\n", val);
		}
	}else{
		/*child process: echo server*/
		int val;
		close(fd[0]);
		while(1){
			read(fd[1], &val, sizeof(val));
			printf("son data received: %d\n", val);
			val++;
			write(fd[1], &val, sizeof(val));
			printf("son send received: %d\n", val);
		}
	}

	return 0;
}
