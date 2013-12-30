/*
 * =====================================================================================
 *
 *       Filename:  jump.c
 *
 *    Description:  jump on c.
 *
 *        Version:  1.0
 *        Created:  05/14/13 11:16:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<setjmp.h>

jmp_buf buf;

void banana(){
	printf("%s", "in banana()\n");
	longjmp(buf,1);
	printf("%s", "you will never see this\n");
}

int main(){
	if(setjmp(buf)){
		printf("%s", "back in main\n");
	}else{
		printf("%s", "first time throught\n");
	}
	printf("you will set twice.\n");
	banana();
}

