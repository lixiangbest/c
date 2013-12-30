/*
 * =====================================================================================
 *
 *       Filename:  hello.c
 *
 *    Description:  hello world.
 *    Usage:		cc hello.c;./a.out;echo $?
 *    				cc -std=c99 hello.c;./a.out;echo $?
 *
 *        Version:  1.0
 *        Created:  05/05/13 20:38:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>

main(){
	printf("size int=%d,short int=%d,long int=%d,float=%d,double=%d\n",sizeof(int),sizeof(short int),sizeof(long int),sizeof(float),sizeof(double));
	printf("hello, world!\n");
}

