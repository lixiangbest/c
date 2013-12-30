/*
 * =====================================================================================
 *
 *       Filename:  lseek.c
 *
 *    Description:  append file.
 *
 *        Version:  1.0
 *        Created:  04/21/13 23:22:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>

#define n 5

int main(int argc,char *argv[]){
	int fd;
	char buf[4096];
	if(argc!=2){
		printf("error, argc must greater than 2!\n");
	}else{
		fd = open(argv[1], O_APPEND|O_RDWR);/*open in append mode.*/

		/*long seek */
		if(lseek(fd, 5, SEEK_SET)==-1){
			printf("cannot seek:%s\n",strerror(errno));
		}
		if(read(fd, buf, n)>0){
			printf("buf=%s\n", buf);
		}
		if(write(fd, buf, n)!=n){
			printf("error write:%s\n",strerror(errno));
		}
	}
	exit(0);
}

