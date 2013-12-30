/*
 * =====================================================================================
 *
 *       Filename:  sleep_us.c
 *
 *    Description:  sleep useconds.
 *
 *        Version:  1.0
 *        Created:  06/01/13 14:08:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<sys/select.h>
#include<sys/poll.h>
#include<sys/time.h>

#define NSEC 1000000
#define NSECF 1000000.00

void sleep_us(unsigned int nusecs){
	struct timeval tval;
	tval.tv_sec = nusecs/NSEC;
	tval.tv_usec = nusecs%NSEC;
	select(0, NULL, NULL, NULL, &tval);
}

void sleep_poll(unsigned int nusecs){
	struct pollfd dummy;
	int timeout;
	/*nusec to nansec*/
	if((timeout = nusecs/1000)<=0)
		timeout = 1;
	poll(&dummy, 0, timeout);
}

int main(void){
	struct timeval tv1,tv2;

	printf("before sleep_us:\n");
	gettimeofday(&tv1, NULL);
	sleep_us(2*NSEC);
	gettimeofday(&tv2, NULL);
	printf("after sleep_us:%f seconds\n",tv2.tv_sec-tv1.tv_sec+tv2.tv_usec/NSECF-tv1.tv_usec/NSECF);

	printf("before sleep_poll:\n");
	gettimeofday(&tv1, NULL);
	sleep_poll(2*NSEC);
	gettimeofday(&tv2, NULL);
	printf("after sleep_poll:%f seconds\n",tv2.tv_usec/NSECF+tv2.tv_sec-tv1.tv_usec/NSECF-tv1.tv_sec);
	return 0;
}
