/*
 * =====================================================================================
 *
 *       Filename:  static.c
 *
 *    Description:  extern and static
 *
 *        Version:  1.0
 *        Created:  05/14/13 12:46:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>

static int me;

void add(){
	me++;
}

int main(){
	static int you;
	printf("me = %d, you = %d\n", me, you);
	add();
	me++;you++;
	printf("me = %d, you = %d\n", me, you);
	return 0;
}

