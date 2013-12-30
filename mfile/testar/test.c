/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  Function test
 *
 *        Version:  1.0
 *        Created:  10/21/12 18:32:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int max(int,int);
void print(char*);

#ifdef EXIT_SUCCESS
#undef EXIT_SUCCESS
#define EXIT_SUCCESS 2
#endif

int main ( int argc, char *argv[] ){
	char buf[80];
	buf[0] = 'a';
	buf[1] = 'b';
	/*use function from archive library*/
	print("Archive file test!\n");
	printf("max=%d\n",max(6,7));
	snprintf(buf+strlen(buf),80-strlen(buf),":%s","permission denied!");
	printf("%s\n",buf);
	printf("%d\n",EXIT_SUCCESS);
	return EXIT_SUCCESS;
}				
/* ----------  end of function main  ---------- */
