/*
 * =====================================================================================
 *
 *       Filename:  getcon.c
 *
 *    Description:  get concurrency.
 *
 *        Version:  1.0
 *        Created:  05/24/13 11:15:23
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

static void sig_hand(int signo){
	if(signo==SIGINT){
		printf("caught SIGINT\n");
	}else if(signo==SIGUSR1){
		printf("caught SIGUSR1\n");
	}
}

int main(void){
	void *thr_fn(void*);
	int err;
	void *tset;
	pthread_t tid;
	if(signal(SIGINT, sig_hand)==SIG_ERR)
		err_sys("signal(SIGINT) error");
	if(signal(SIGUSR1, sig_hand)==SIG_ERR)
		err_sys("signal(SIGUSR1) error");

	err = pthread_create(&tid, NULL, thr_fn, NULL);
	if(err != 0){
		err_quit("can't create thread: %s\n", strerror(err));
	}
	/* the main thread is block until the new thread exit or return.
	err = pthread_join(tid,&tset);
	if(err != 0){
		err_quit("can't join with thread: %s\n", strerror(err));
	}
	printf("thread exit code %d\n",(int)tset);
	*/
	sleep(5);
	printf("tid=0x%x\n",(unsigned long)tid);
	exit(0);
}

void *thr_fn(void *arg){
	/*sleep(2);*/
	kill(getpid(),SIGUSR1);/*thread send signal.*/
	printf("get concurrency:%d\n", pthread_getconcurrency());/**/
	kill(getpid(),SIGINT);/*thread send signal.*/
	return((void*)0);
}
