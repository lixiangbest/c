/*
 * =====================================================================================
 *
 *       Filename:  01_init.c
 *
 *    Description:  init daemonize usage.
 *
 *        Version:  1.0
 *        Created:  05/26/13 16:21:24
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
	void daemonize(const char *);
	daemonize("hello, world");
	while(1) sleep(1);
	return 0;
}

