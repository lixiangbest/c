/*************************************************************************
	> File Name: pipe.c
	> Description: pipe communication.
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月17日 星期二 23时07分38秒
 ************************************************************************/
#include "unp.h"

int main(){
	int fd1[2], fd2[2];
	pipe(fd1);
	pipe(fd2);

	if( fork() ){
		/*Parent process: echo client*/
		int val = 0;
		close(fd1[0]);
		close(fd2[1]);
		while(1){
			sleep(1);
			val++;
			printf("parent sending data: %d\n", val);
			write(fd1[1], &val, sizeof(val));
			read(fd2[0], &val, sizeof(val));
			printf("parent data received: %d\n", val);
		}
	}else{
		/*Child process: echo server*/
		int val;
		close(fd1[1]);
		close(fd2[0]);
		while(1){
			read(fd1[0], &val, sizeof(val));
			printf("son data received: %d\n", val);
			val++;
			write(fd2[1], &val, sizeof(val));
			printf("son send received: %d\n", val);
		}
	}
}
