/*
 * =====================================================================================
 *
 *       Filename:  02_hole.c
 *
 *    Description:  create an empty file.
 *
 *        Version:  1.0
 *        Created:  04/20/13 18:23:40
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

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void){
	int fd;
	printf("S_IRUSR=%d,S_IWUSR=%d,S_IRGRP=%d,S_IROTH=%d,|=%d\n",S_IRUSR,S_IWUSR,S_IRGRP,S_IROTH,(S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH));
	if((fd=creat("file.hole", FILE_MODE)) < 0)
		err_sys("creat error");

	if(write(fd, buf1, 10)!=10)
		err_sys("lseek error");
	/*offset now = 10*/

	if(lseek(fd, 16384, SEEK_SET) == -1)
		err_sys("lseek error");
	/*offset now = 16384*/

	if(write(fd, buf2, 10)!=10)
		err_sys("buf2 write error");
	/*offset now = 16394*/

	exit(0);
}
