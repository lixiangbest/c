/*
 * =====================================================================================
 *
 *       Filename:  suspend.c
 *
 *    Description:  thread suspend
 *
 *        Version:  1.0
 *        Created:  05/25/13 15:44:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<pthread.h>

int quitflag;/*set nonzero by thread*/
sigset_t mask;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t waitloc = PTHREAD_COND_INITIALIZER;

static void sig_int(int signo){
	printf("catch sigint:%ld\n",(unsigned long)pthread_self());
}

void *thr_fn(void *arg){
	int err, signo;
	signal(SIGINT, sig_int);/*signal handler.*/
	for(;;){
		printf("new thread sigwait\n");
		err = sigwait(&mask, &signo);/*sigmask signo*/
		if(err != 0){
			err_exit(err, "sigwait failed");
		}
		switch(signo){
			case SIGINT:
				printf("\ninterrupt\n");
				break;/*break switch*/
			case SIGQUIT:
				printf("\nquit\n");
				pthread_mutex_lock(&lock);
				quitflag = 1;
				pthread_mutex_unlock(&lock);
				pthread_cond_signal(&waitloc);/*wake up the thread waiting for the condition.*/
				return(0);
			default:
				printf("unexpected signal %d\n", signo);
				exit(1);
		}
	}
}

int main(void){
	int err;
	sigset_t oldmask;
	pthread_t tid;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	/*before call the sigwait, you must block the signals that thread is waiting for.*/
	if((err = pthread_sigmask(SIG_BLOCK, &mask, &oldmask)) != 0)
		err_exit(err, "SIG_BLOCK error");
	/*create a new thread.*/
	err = pthread_create(&tid, NULL, thr_fn, 0);
	if(err != 0){
		err_exit(err, "can't create thread");
	}
	printf("success to create a new thread\n");

	pthread_mutex_lock(&lock);
	while(quitflag == 0){/*while change to if*/
		printf("you will see block in main thread!\n");
		pthread_cond_wait(&waitloc, &lock);
	}
	pthread_mutex_unlock(&lock);

	/*SIGQUIT has been caught and is now blocked; do whatever*/
	quitflag = 0;
	printf("main thread quitflag = %d\n", quitflag);

	/*reset signal mask which unblocks SIGQUIT*/
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
		err_sys("SIG_SETMASK error");
	}
	sleep(1);/*new thread sig_int is not useful.*/
	exit(0);
}
