/*
 * =====================================================================================
 *
 *       Filename:  format_io.c
 *
 *    Description:  format io function usage.
 *
 *        Version:  1.0
 *        Created:  04/30/13 17:38:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>
#define MAX 50

int main(){
	char buf[MAX];
	char nbuf[5];
	int scan;

	printf("stdin fileno=%d\n",fileno(stdin));

	printf("printf usage:%d\n",3);
	fprintf(stdout,"fprintf usage:%d\n",3);
	
	sprintf(buf,"sprintf to buf:%d\n",3);
	fputs(buf,stdout);

	snprintf(nbuf,5,"snprintf to buf:%d\n",10);
	fputs(nbuf,stdout);
	
	printf("\nplease enter the scan:%%d\n");
	scanf("%d",&scan);
	printf("scan=%d\n",scan);
	return 0;
}

