/*
 * =====================================================================================
 *
 *       Filename:  07_uidgid.c
 *
 *    Description:  output the current login user id and its group id.
 *
 *        Version:  1.0
 *        Created:  04/18/13 23:06:02
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
	printf("uid = %d, gid = %d\n", getuid(), getgid());
	exit(0);
}
