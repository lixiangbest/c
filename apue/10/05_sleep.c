/*
 * =====================================================================================
 *
 *       Filename:  05_sleep.c
 *
 *    Description:  my sleep function usage.
 *
 *        Version:  1.0
 *        Created:  05/14/13 09:42:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

unsigned int sleep1(unsigned int);

static void sig_alarm(int signo){
	printf("sig_alarm\n");
}

int main(void){
	if(signal(SIGALRM, sig_alarm) == SIG_ERR){
		err_sys("sig_alarm error\n");
	}
	alarm(2);
	/*sleep(3);*/
	printf("sleep seconds = %d\n", sleep1(3));
	pause();
	return 0;
}

