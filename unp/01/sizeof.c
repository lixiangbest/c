/*
 * =====================================================================================
 *
 *       Filename:  sizeof.c
 *
 *    Description:  sizeof type.
 *
 *        Version:  1.0
 *        Created:  07/07/13 09:29:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

int main(){
	int *p, q, x;
	x = 10;
	p = &x;
	*p = x+1;
	q = x;
	printf("q=%d\n", q);
	printf("sizeof short int %d\n", sizeof(short));
	printf("sizeof int %d\n", sizeof(int));
	printf("sizeof unsigned int %d\n", sizeof(unsigned int));
	printf("sizeof long int %d\n", sizeof(long int));
	printf("sizeof float %d\n", sizeof(float));
	printf("sizeof double %d\n", sizeof(double));
	printf("sizeof size_t %d\n", sizeof(size_t));
	printf("sizeof ssize_t %d\n", sizeof(ssize_t));
	return 0;
}

