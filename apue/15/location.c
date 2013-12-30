/*
 * =====================================================================================
 *
 *       Filename:  location.c
 *
 *    Description:  location-value; Read-value;
 *
 *        Version:  1.0
 *        Created:  06/03/13 21:52:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>

int main(void){
	int a = 3;
	const int b = 5;
	printf("a = %d, b = %d\n", a, b);
	a = b+2;
	/*b = a+2;*//*error: assignment of read-only variable 'b'*/
	printf("a = %d, b = %d\n", a, b);
	(a=4)+= 28;
	printf("a = %d, b = %d\n", a, b);
}
