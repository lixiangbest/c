/*
 * =====================================================================================
 *
 *       Filename:  segfault2.c
 *
 *    Description:  segmentation falut example2.
 *
 *        Version:  1.0
 *        Created:  06/30/13 16:09:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<stdlib.h>

int  main(){
	int *ptr = (int*)0;
	*ptr = 100;

	return 0;
}

