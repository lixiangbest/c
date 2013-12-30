/*
 * =====================================================================================
 *
 *       Filename:  putenv_r.c
 *
 *    Description:  putenv
 *
 *        Version:  1.0
 *        Created:  05/25/13 18:35:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<limits.h>
#include<pthread.h>
#include<errno.h>
#include<string.h>

extern char **environ;

pthread_mutex_t env_mutex;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;

static void thread_init(void){
	pthread_mutexattr_t attr;

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&env_mutex, &attr);
	pthread_mutexattr_destroy(&attr);
}

/*char *string = "USER=root";*/
int putenv_r(char *string){
	exit(0);
}
