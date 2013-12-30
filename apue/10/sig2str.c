/*
 * =====================================================================================
 *
 *       Filename:  sig2str.c
 *
 *    Description:  my sig2str function
 *
 *        Version:  1.0
 *        Created:  05/19/13 22:04:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

int main(int argc, char **argv){
	if(argc!=2){
		printf("usage: %s sig_num\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int sig;
	sig = atoi(argv[1]);
	printf("%s\n", strsignal(sig));
	return 0;
}
