/*
 * =====================================================================================
 *
 *       Filename:  tsleep2.c
 *
 *    Description:  tsleep2
 *
 *        Version:  1.0
 *        Created:  05/14/13 10:41:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

unsigned int sleep2(unsigned int);
void sig_int(int);

int main(void){
	unsigned int unslept;
	if(signal(SIGINT, sig_int)==SIG_ERR){
		err_sys("signal(SIGINT) error");
	}
	unslept = sleep2(10);
	printf("sleep2 returned: %u\n", unslept);
	exit(0);
}

void sig_int(int signo){
	int i,j;
	volatile int k;
	
	/*
	 * Tune these loops to run for more than 5 seconds
	 * on whatever system this test program is run.
	 */
	printf("\nsig_int starting\n");
	for(i=0;i<30000;i++)
		for(j=0;j<4000;j++)
			k += i*j;
	printf("sig_int finished:%d\n",k);
}

