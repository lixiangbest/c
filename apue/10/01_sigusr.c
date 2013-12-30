/*
 * =====================================================================================
 *
 *       Filename:  01_sigusr.c
 *
 *    Description:  signal user
 *    			$ ./a.out &
 *    			$ kill -USR1 7216
 *    			$ kill -USR2 7216
 *    			$ kill 7216
 *
 *        Version:  1.0
 *        Created:  05/14/13 02:14:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

static void sig_usr(int);/*one handler for both singals*/

int main(void){
	if(signal(SIGUSR1, sig_usr) == SIG_ERR){
		err_sys("can't catch SIGUSR1");
	}
	if(signal(SIGUSR2, sig_usr) == SIG_ERR){
		err_sys("can't catch SIGUSR2");
	}
	for(;;){
		pause();/*hang up when received a signal*/
	}
	return 0;
}

static void sig_usr(int signos){/*argument is signal number*/
	if(signos == SIGUSR1)
		printf("received SIGUSR1\n");
	else if(signos == SIGUSR2){
		printf("received SIGUSR2\n");
	}else{
		err_dump("received signal %d\n", signos);
	}
}
