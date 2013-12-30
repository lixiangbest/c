/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  Makefile test
 *
 *        Version:  1.0
 *        Created:  11/03/12 16:05:35
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

int	main(int argc, char *argv[]){
	int i=0;
	printf("%d\n",argc);
	while(i<argc){
		printf("%s\n",argv[i]);
		i++;
	}
	return EXIT_SUCCESS;
}
/* ----------  end of function main  ---------- */

