/*
 * =====================================================================================
 *
 *       Filename:  unlink.c
 *
 *    Description:  unlink
 *
 *        Version:  1.0
 *        Created:  04/29/13 14:58:43
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
#include<errno.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc, int *argv[]){
	char *path;
	int fd;

	if(argc != 2){
		printf("error argv");
		exit(0);
	}
	path = argv[1];

	if(unlink(path) < 0){
		printf("%s unlink error %d:%s\n",path,errno,strerror(errno));
	}
	if((fd = creat(path, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) < 0){
		printf("%s creat error %d:%s\n",path,errno,strerror(errno));
	}else{
		printf("fd = %d\n",fd);
	}
	return 0;
}

