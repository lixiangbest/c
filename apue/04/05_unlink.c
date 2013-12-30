/*
 * =====================================================================================
 *
 *       Filename:  05_unlink.c
 *
 *    Description:  unlink a file.
 *
 *        Version:  1.0
 *        Created:  04/24/13 02:29:51
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

int main(void){
	if(open("tempfile", O_RDWR) < 0)
		err_sys("open error");
	if(unlink("tempfile") < 0)
		err_sys("unlink error");
	printf("file unlinked\n");
	sleep(15);
	printf("done\n");
	exit(0);
}

