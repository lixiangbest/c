/*
 * =====================================================================================
 *
 *       Filename:  segfault3.c
 *
 *    Description:  segmentation fault example.
 *
 *        Version:  1.0
 *        Created:  06/30/13 16:19:05
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
#include<string.h>

int  main(){
	char *ptr = "test";
	strcpy(ptr, "TEST");

	return 0;
}
