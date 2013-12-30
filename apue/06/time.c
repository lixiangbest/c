/*
 * =====================================================================================
 *
 *       Filename:  time.c
 *
 *    Description:  time function
 *
 *        Version:  1.0
 *        Created:  05/01/13 20:02:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<time.h>

int main(){
	time_t caltime;
	struct tm *tm;
	char line[1024];

	int t = 0x7fffffff;
	time_t *timet;
	timet =(time_t*)&t;
	printf("%d\n",t);
	printf("localtime = %s",ctime(timet));

	if((caltime = time(NULL))==-1){
		return 1;
	}
	if((tm = localtime(&caltime)) == NULL)
		return 1;

	if(strftime(line, 1024, "%a %b %d %X %Z %Y\n", tm) == 0)
		return 1;
	
	fputs(line, stdout);
	return 0;
}

