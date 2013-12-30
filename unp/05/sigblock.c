/*
 * =====================================================================================
 *
 *       Filename:  sigblock.c
 *
 *    Description:  signal block.
 *
 *        Version:  1.0
 *        Created:  07/16/13 22:07:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<signal.h>
#include<stdio.h>
#include<unistd.h>

void printsigset(const sigset_t *set){
	int i;
	for(i = 1; i < 32; i++){
		/*current signal is the member of i*/
		if( sigismember(set, i) == 1)
			putchar('1');
		else
			putchar('0');
	}
	puts("");
}

int main(void){
	sigset_t s, p;
	sigemptyset(&s);
	sigaddset(&s, SIGINT);
	sigprocmask(SIG_BLOCK, &s, NULL);
	while(1){
		sigpending(&p);/*get the pending signal.*/
		printsigset(&p);
		sleep(1);
	}
	return 0;
}
