/*
 * =====================================================================================
 *
 *       Filename:  endian.c
 *
 *    Description:  client little-endian and server big-endian.
 *
 *        Version:  1.0
 *        Created:  07/20/13 18:13:46
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
	short m;
	int n;
	printf("sizeof char:%d, sizeof short int:%d, sizeof int:%d, sizeof long int:%d\n", sizeof(char), sizeof(short), sizeof(int), sizeof(long));

	m = 0x2ffe;
	n = (int)m;
	printf("m=%d, 0x%x, n=0x%x\n", m, m, n);
	m = (short)htons(m);
	n = (int)m;
	printf("m=%d, 0x%x, n=0x%x\n", m, m, n);

	/*little-endian*/
	printf("a = 0x%x, b = 0x%x, a+b = 0x%x\n", 0xffffffea, 0xffffffb3, 0xffffffea+0xffffffb3);
	printf("a = 0x%x, b = 0x%x, a+b = 0x%x\n", 0xeaffffff, 0xb3ffffff, 0xeaffffff+0xb3ffffff);
	
	return 0;
}

