/*
 * =====================================================================================
 *
 *       Filename:  endian.c
 *
 *    Description:  check the endian
 *
 *        Version:  1.0
 *        Created:  06/12/13 16:32:09
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
#include<inttypes.h>

int main(void){
	uint32_t i;
	unsigned char *cp;
	i = 0x04030201;
	cp = (unsigned char *)&i;
	printf("&i:0x%x,cp:0x%x\n", &i, cp);
	if(*cp == 1){
		printf("little-endian\n");
	}else if(*cp == 4){
		printf("big-endian\n");
	}else{
		printf("who knows?\n");
	}
	exit(0);
}

