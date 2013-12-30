/*
 * =====================================================================================
 *
 *       Filename:  02_access.c
 *
 *    Description:  file access test.
 *
 *        Version:  1.0
 *        Created:  04/23/13 21:51:51
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

int main(int argc, char *argv[]){
	if(argc != 2)
		err_quit("usage: a.out <pathname>");
	
	/*whether read ok*/
	if(access(argv[1], R_OK) < 0){
		err_ret("access error fo %s", argv[1]);
	}else{
		printf("read access OK\n");
	}

	if(open(argv[1], O_RDONLY) < 0){
		err_ret("open error for %s", argv[1]);
	}else{
		printf("open for reading OK\n");
	}
	exit(0);
}

