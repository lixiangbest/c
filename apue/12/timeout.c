/*
 * =====================================================================================
 *
 *       Filename:  timeout.c
 *
 *    Description:  timeout
 *
 *        Version:  1.0
 *        Created:  05/24/13 15:45:26
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
#include<time.h>
#include<sys/time.h>

extern int makethread(void *(*)(void *), void *);

struct to_info{
	void (*to_fn)(void*);/*function*/
	void *to_arg;/*argument*/
	struct timespec to_wait;/*time to wait*/
};/*you must the ;*/

#define SECTONSEC  1000000000	/*seconds to nanoseconds*/
#define USECTONSEC 1000		/*microseconds to nanoseconds*/

void *timeout_helper(void *arg){
	struct to_info *tip;

	tip = (struct to_info*)arg;
	printf("this is timeout_helper\n");
	printf("tv_sec:%ld,tv_nesc:%ldi\n",(unsigned long)tip->to_wait.tv_sec,(unsigned long)tip->to_wait.tv_nsec);
	nanosleep(&tip->to_wait, NULL);
	(*tip->to_fn)(tip->to_arg);
	return(0);
}

void timeout(const struct timespec *when, void (*func)(void*), void *arg){
	struct timespec now;
	struct timeval tv;
	struct to_info *tip;
	int	err;

	gettimeofday(&tv, NULL);
	printf("tv tv_sec:%ld,tv_uesc:%ld\n",(unsigned long)tv.tv_sec,(unsigned long)tv.tv_usec);
	now.tv_sec = tv.tv_sec;
	now.tv_nsec = tv.tv_usec * USECTONSEC;/*usec to nsec*/
	printf("when tv_sec:%ld,tv_nesc:%ld\n",(unsigned long)when->tv_sec,(unsigned long)when->tv_nsec);
	printf("now tv_sec:%ld,tv_nesc:%ld\n",(unsigned long)now.tv_sec,(unsigned long)now.tv_nsec);
	/*when is later than now*/
	if((when->tv_sec > now.tv_sec) || (when->tv_sec == now.tv_sec && when->tv_nsec > now.tv_nsec)){
		tip = malloc(sizeof(struct to_info));
		if(tip!=NULL){
			tip->to_fn = func;
			tip->to_arg = arg;
			tip->to_wait.tv_sec = when->tv_sec - now.tv_sec;
			if(when->tv_nsec >= now.tv_nsec){
				tip->to_wait.tv_nsec = when->tv_nsec - now.tv_nsec;
			}else{
				tip->to_wait.tv_sec--;
				tip->to_wait.tv_nsec = SECTONSEC - now.tv_nsec+when->tv_nsec;
			}
			/*create new thread.*/
			err = makethread(timeout_helper, (void *)tip);
			if(err == 0)
				return;
		}
	}
	/*
	 * We get here if (a) when <= now, or (b) malloc fails, or (c) we 
	 * can't make a thread, so we just call the function now.
	 */
	(*func)(arg);
}

pthread_mutexattr_t attr;/*mutex attribute.*/
pthread_mutex_t mutex;/*mutex*/

void retry(void *arg){
	pthread_mutex_lock(&mutex);
	/*perform retry steps...*/
	printf("this is retry\n");
	pthread_mutex_unlock(&mutex);
}

int main(void){
	int err, condition, arg;
	struct timespec when;
	struct timeval tv;
	/*init the mutex attribute.*/
	if((err = pthread_mutexattr_init(&attr)) != 0){
		err_exit(err, "pthread_mutexattr_init failed");
	}
	/*set the mutex attribute as recursive.*/
	if((err = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)) != 0)
		err_exit(err, "can't set recursive type");
	/*init the mutex.*/
	if((err = pthread_mutex_init(&mutex, &attr))!=0){
		err_exit(err, "can't create recursive mutex");
	}
	/*...*/
	gettimeofday(&tv,NULL);
	/*when.tv_sec = tv.tv_sec - 1;*/
	when.tv_sec = tv.tv_sec + 1;
	when.tv_nsec = tv.tv_usec * USECTONSEC;
	pthread_mutex_lock(&mutex);
	/*...*/
	if(condition){
		/*calculate target time "when" */
		timeout(&when, retry, (void *)arg);
	}
	/*...*/
	pthread_mutex_unlock(&mutex);
	/*...*/
	sleep(2);
	exit(0);
}
