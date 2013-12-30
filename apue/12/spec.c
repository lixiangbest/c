/*
 * =====================================================================================
 *
 *       Filename:  spec.c
 *
 *    Description:  nanosecond.
 *    Usage:		gcc -lrt -o spec spec.c
 *
 *        Version:  1.0
 *        Created:  05/24/13 16:09:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<time.h>
#include<stdio.h>
#include<string.h>
/**
 * struct timespec{
 *		time_t tv_sec;//second
 *		long tv_nsec;//nanosecond
 * }
 */

int main(void){
	struct timespec time;
	memset(&time, 0, sizeof(time));/*space initialization*/
	clock_gettime(CLOCK_REALTIME, &time);
	printf("%d------>%d\n", time.tv_sec, time.tv_nsec);
	return 0;
}

