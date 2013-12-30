/*
 * =====================================================================================
 *
 *       Filename:  getenv.c
 *
 *    Description:  getenv usage.
 *
 *        Version:  1.0
 *        Created:  05/25/13 20:56:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<time.h>

/*thread security*/
unsigned my_sleep(unsigned nsec){
	int n;
	unsigned slept;
	time_t start, end;
	struct timeval tv;/*gettimeofday*/

	tv.tv_sec = nsec;
	tv.tv_usec = 0;
	time(&start);
	n = select(0, NULL, NULL, NULL, &tv);
	if(n==0){
		return 0;
	}
	time(&end);
	slept = end -start;
	if(slept>=nsec)
		return 0;
	return(nsec-slept);
}

int main(void){
	char *getenv3(char *);
	printf("%s\n", getenv3("PWD"));
	printf("%d\n", my_sleep(5));
	exit(0);
}

