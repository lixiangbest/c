/*
 * =====================================================================================
 *
 *       Filename:  03_umask.c
 *
 *    Description:  umask function usage.
 *
 *        Version:  1.0
 *        Created:  04/23/13 22:27:07
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

#define RWRWRW (S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(void){
	/*umask(0);*/
	if(creat("myfoo", RWRWRW) < 0)
		err_sys("creat error for foo");
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if(creat("mybar", RWRWRW) < 0)
		err_sys("creat error for bar");
	
	exit(0);
}

