/*
 * =====================================================================================
 *
 *       Filename:  close.c
 *
 *    Description:  close the fd 0, 1, 2
 *
 *        Version:  1.0
 *        Created:  05/26/13 16:06:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<fcntl.h>
#include<stdio.h>

int main(void){
	int fd0,fd1,fd2;
	FILE *fp;
	close(0);close(1);close(2);/*close the standard input,output,err*/
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);
	
	fp = fopen("close.txt", "w");
	fprintf(fp, "fd0:%d;fd1:%d;fd2:%d\n", fd0, fd1, fd2);
}

