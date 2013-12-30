/*
 * =====================================================================================
 *
 *       Filename:  sleep1.c
 *
 *    Description:  my sleep complish.
 *
 *        Version:  1.0
 *        Created:  05/14/13 09:28:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<signal.h>
#include<unistd.h>

static void sig_alrm(int signo){
	/*nothing to do, just return to wake up the pause*/
	printf("sigalarm in sleep1.c\n");
}

unsigned int sleep1(unsigned int nsecs){
	if(signal(SIGALRM, sig_alrm)==SIG_ERR)
		return(nsecs);
	printf("alarm sleep1 = %d\n", alarm(nsecs));/*start the timer*/
	pause();/*next caught signal wakes us up*/
	return(alarm(0));/*turn off timer, return unslept time*/
}

