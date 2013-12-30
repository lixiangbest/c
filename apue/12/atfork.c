/*
 * =====================================================================================
 *
 *       Filename:  atfork.c
 *
 *    Description:  at fork
 *
 *        Version:  1.0
 *        Created:  05/25/13 17:15:25
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
#include<sys/wait.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void prepare(void){
	printf("preparing locks...\n");
	pthread_mutex_lock(&lock1);
	pthread_mutex_lock(&lock2);
}

void parent(void){
	printf("parent unlocking locks...\n");
	pthread_mutex_unlock(&lock1);
	pthread_mutex_unlock(&lock2);
}

void child(void){
	printf("child unlocking locks...\n");
	pthread_mutex_unlock(&lock1);
	pthread_mutex_unlock(&lock2);
}

void *thr_fn(void *arg){
	printf("thread started...\n");
	pause();
	printf("after pause...\n");
	return 0;
}

int main(void){
	int err;
	pid_t pid;
	pthread_t tid;
#if defined(BSD) || defined(MACOS)
	printf("pthread_atfork is unsupported\n");
#else
	if((err = pthread_atfork(prepare, parent, child)) != 0)
		err_exit(err, "can't install fork handlers");
	err = pthread_create(&tid, NULL, thr_fn, 0);
	if(err != 0){
		err_exit(err, "can't create thread");
	}
	sleep(2);
	printf("parent about to fork...\n");
	if((pid = fork()) < 0){
		err_quit("fork failed");
	}else if(pid==0){/*child*/
		printf("child returned from fork\n");
	}else{
		printf("parent returned from fork\n");
		if(waitpid(pid,NULL,0) < 0){
			err_sys("wait error!");
		}
	}
#endif
	exit(0);
}
