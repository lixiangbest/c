/*
 * =====================================================================================
 *
 *       Filename:  detach.c
 *
 *    Description:  detach
 *
 *        Version:  1.0
 *        Created:  05/24/13 00:04:49
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

int makethread(void *(*fn)(void*), void *arg){
	int err;
	pthread_t tid;/*thread id*/
	pthread_attr_t attr;/*thread attribute*/

	err = pthread_attr_init(&attr);
	if(err != 0){
		return err;
	}
	err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	/*call success, create a new thread.*/
	if(err == 0)
		err = pthread_create(&tid, &attr, fn, arg);
	/*destroy the pthread attribute.*/
	pthread_attr_destroy(&attr);
	return(err);
}

