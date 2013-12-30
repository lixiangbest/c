/*
 * =====================================================================================
 *
 *       Filename:  calloc.c
 *
 *    Description:  calloc function
 *
 *        Version:  1.0
 *        Created:  05/07/13 22:15:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdlib.h>
#include<stdio.h>

int main(void){
	int *arr;
	int *parr[5];
	arr = (int*)calloc(10, sizeof(int));
	printf("initlize calloc arr[0]=%d,arr[1]=%d\n",arr[0],arr[1]);

	parr[0] = (int*)calloc(3,sizeof(int));
	parr[1] = (int*)calloc(3,sizeof(int));
	printf("initlize calloc parr[0]=%d,parr[1]=%d\n",parr[0],parr[1]);
}

