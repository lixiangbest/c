/*
 * =====================================================================================
 *
 *       Filename:  fdtest.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/12/13 00:49:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc, char *argv[]){
	int fd;
	int val;
	sscanf(argv[1], "%d\0", &fd);
	/*printf("fd=%d\n",fd);*/
	if((val = fcntl(fd, F_GETFD, 0)) < 0){
		//perror("fcntl error!");
		//return(1);
	}

	printf("fd=%d,val=%d\n",fd,val);
	if(val<0){
		printf("close-on-exec is off\n");
	}else{
		printf("close-on-exec is on\n");
	}
	return 0;
}

