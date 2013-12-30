/*
 * =====================================================================================
 *
 *       Filename:  09_cdpwd.c
 *
 *    Description:  cd pwd cmd
 *
 *        Version:  1.0
 *        Created:  04/24/13 15:18:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

int main(void){
	char *ptr;
	int size;

	if(chdir("/usr/local/man") < 0)
		err_sys("chdir failed");

	ptr = path_alloc(&size);/*our own function*/
	if(getcwd(ptr, size) == NULL)
		err_sys("getcwd failed");
	printf("path size=%d\n",size);
	printf("cwd=%s\n", ptr);
	exit(0);
}

