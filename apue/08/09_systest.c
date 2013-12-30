/*
 * =====================================================================================
 *
 *       Filename:  09_systest.c
 *
 *    Description:  sys test.
 *    Usage:		09_systest 10_pruids
 *    				Notice the path.
 *
 *        Version:  1.0
 *        Created:  05/11/13 17:59:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

int main(int argc, char *argv[]){
	int status;

	if(argc < 2){
		err_quit("command-line argument required");
	}

	if((status = system(argv[1]))<0){
		err_sys("system() error");
	}
	/*get exit status*/
	pr_exit(status);

	exit(0);
}

