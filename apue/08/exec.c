/*
 * =====================================================================================
 *
 *       Filename:  exec.c
 *
 *    Description:  get exec FD_CLOEXEC
 *
 *        Version:  1.0
 *        Created:  05/12/13 00:40:25
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
#include<stdlib.h>
#include<dirent.h>
#include<fcntl.h>

int main(){
	DIR *dp = opendir("/");
	int fd = dirfd(dp);/*new function for SUS*/
	int val = fcntl(fd,F_GETFD,0);
	pid_t pid;
	char fdstr[12];
	
	if(val&FD_CLOEXEC){
		printf("close-on-exec is on\n");
	}else{
		printf("close-on-exec is off\n");
	}
	
	sprintf(fdstr, "%d\0", fd);
	printf("fdstr=%s\n",fdstr);
	if((pid=fork())<0)
		perror("fork error");
	else if(pid==0){
		execl("/home/suncco/c/apue/08/fdtest","fdtest",fdstr,NULL);
		exit(0);
	}
	exit(0);
}

