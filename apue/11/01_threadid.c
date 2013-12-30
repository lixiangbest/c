/*
 * =====================================================================================
 *
 *       Filename:  01_threadid.c
 *
 *    Description:  threadid
 *
 *        Version:  1.0
 *        Created:  05/21/13 02:15:03
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

pthread_t ntid;

void printids(const char *s){
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid, (unsigned int)tid, (unsigned int)tid);
}

void *thr_fn(void *arg){
	printf("in new thread:%u\n", (unsigned int)ntid);
	printids("new thread: ");
	/*_exit(0);*//*process exit.*/
	return((void *)0);
}

int main(){
	int err;
	/*printids("In main thread:");*/
	printf("In main function:pid %u tid %u (0x%x)\n", (unsigned int)getpid(), (unsigned int)pthread_self(), (unsigned int)pthread_self());
	/*ntid is global variable.*/
	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	if(err!=0){
		err_quit("can't create thread: %s\n", strerror(err));
	}
	printf("new thread:%u\n", (unsigned int)ntid);
	printids("In main thread:");
	sleep(1);/*main thread need to sleep.wait for the new thread running.Or main chread is end, new thread is running.you can't not see the new thread id print.*/
	printf("sleep.\n");
	exit(0);
}
