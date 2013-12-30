/*
 * =====================================================================================
 *
 *       Filename:  fdsize.c
 *
 *    Description:  fd set size
 *
 *        Version:  1.0
 *        Created:  06/01/13 21:03:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#define FD_SETSIZE 2
#include "apue.h"
#include<fcntl.h>

int main(void){
	int fd,fdcount = 0;
	printf("FD_SETSIZE:%d\n", FD_SETSIZE);

	if((fd = open("mto.txt", O_RDWR|O_CREAT, FILE_MODE)) < 0){
		err_sys("open error!");
	}
	fdcount++;/*open fd amount*/
	
	while(fd>0){
		if((fd = open("mto.txt", O_RDWR, FILE_MODE)) < 0){
			perror("open error!");
			break;
		}else{
			fdcount++;
		}
	}
	printf("open file is:%d\n", fdcount+3);
	return 0;
}
