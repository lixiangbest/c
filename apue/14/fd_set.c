/*
 * =====================================================================================
 *
 *       Filename:  fd_set.c
 *
 *    Description:  fd_set config
 *
 *        Version:  1.0
 *        Created:  05/28/13 11:36:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<sys/select.h>

int main(void){
	fd_set readset;
	
	printf("FD_SETSIZE=0x%x\n", sysconf(FD_SETSIZE));
	printf("_SC_PAGESIZE=0x%x\n", sysconf(_SC_PAGESIZE));
	printf("_SC_PAGESIZE=%d\n", sysconf(_SC_PAGESIZE));
	printf("readset=0x%x\n", readset);

	return 0;
}

