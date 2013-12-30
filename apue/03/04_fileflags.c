/*
 * =====================================================================================
 *
 *       Filename:  04_fileflags.c
 *
 *    Description:  open file flags.
 *    				./a.out 0 < /dev/tty
 *    				./a.out 1 > temp.foo
 *    				./a.out 2 2>>temp.foo
 *
 *        Version:  1.0
 *        Created:  04/20/13 22:39:15
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

int main(int argc, char *argv[]){
	int val;
	if(argc!=2){
		err_quit("usage: a.out <descriptor#>");
	}

	if((val=fcntl(atoi(argv[1]), F_GETFL, 0))<0){
		err_sys("fcntl error for fd %d", atoi(argv[1]));
	}
	printf("val=%d,O_ACCMODE=%d\n",val,O_ACCMODE);
	switch(val & O_ACCMODE){
		case O_RDONLY:
			printf("read only=%d,",O_RDONLY);
			break;
		case O_WRONLY:
			printf("write only=%d,",O_WRONLY);
			break;
		case O_RDWR:
			printf("read write=%d,",O_RDWR);
			break;
		default:
			err_dump("unknown access mode");
	}

	if(val & O_APPEND){
		printf(", append=%d",O_APPEND);
	}
	if(val & O_NONBLOCK){
		printf(", nonblocking=%d",O_NONBLOCK);
	}
#if defined(O_SYNC)
	if(val & O_SYNC){
		printf(", synchronous writes=%d",O_SYNC);
	}
#endif
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC)
	if(val & O_FSYNC)
		printf(", synchronous writes=%d",O_FSYNC);
#endif
	putchar('\n');
	exit(0);
}
