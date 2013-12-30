/*
 * =====================================================================================
 *
 *       Filename:  test1.c
 *
 *    Description:  test the dup
 *
 *        Version:  1.0
 *        Created:  04/21/13 22:22:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>

int main(){
	int fd;
	char buf[4096];
	fd = open("/dev/fd/0", O_RDONLY);
	close(0);
	printf("%d\n",fd);
	if(read(fd,buf,4096)>0){
		printf("%s",buf);
	}else{
		printf("%s",strerror(errno));
	}
	return 0;
}
