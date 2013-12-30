/*
 * =====================================================================================
 *
 *       Filename:  10_pruids.c
 *
 *    Description:  print uids.
 *
 *        Version:  1.0
 *        Created:  05/11/13 18:06:53
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
	printf("real uid=%d, effective uid=%d\n", getuid(), geteuid());
	exit(0);
}

