/*
 * =====================================================================================
 *
 *       Filename:  hello2.c
 *
 *    Description:  hello2.c
 *
 *        Version:  1.0
 *        Created:  05/07/13 23:05:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>

int f1(int val){
	int *ptr;
	if(val==0){
		int val;
		val = 5;
		ptr = &val;
	}
	return(*ptr+1);
}

int main(){
	printf("%d\n", f1(0));
	printf("%d\n", f1(5));
	return 0;
}
