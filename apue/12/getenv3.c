/*
 * =====================================================================================
 *
 *       Filename:  getenv3.c
 *
 *    Description:  getenv function
 *
 *        Version:  1.0
 *        Created:  05/25/13 10:55:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<limits.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>

static pthread_key_t key;/*key related to thread private data.*/
static pthread_once_t init_done = PTHREAD_ONCE_INIT;/*pthread once*/
pthread_mutex_t env_mutex = PTHREAD_MUTEX_INITIALIZER;/*pthread mutex*/

extern char **environ;

static void thread_init(void){
	pthread_key_create(&key, free);/*create key*/
}

char *getenv3(const char *name){
	int i,len;
	char *envbuf;
	/*thread_init call only once.*/
	pthread_once(&init_done, thread_init);/*init flag.*/
	pthread_mutex_lock(&env_mutex);
	envbuf = (char *)pthread_getspecific(key);
	if(envbuf == NULL){/*no private data with key*/
		envbuf = malloc(1000);/*ARG_MAX not defined.*/
		if(envbuf == NULL){
			pthread_mutex_unlock(&env_mutex);
			return(NULL);
		}
		pthread_setspecific(key, envbuf);/*key related to private envbuf.*/
	}
	len = strlen(name);
	for(i=0;environ[i]!=NULL;i++){
		if((strncmp(name, environ[i], len) == 0) &&(environ[i][len]=='=')){
			strcpy(envbuf, &environ[i][len+1]);/*copy to thread private envbuf*/
			pthread_mutex_unlock(&env_mutex);
			return(envbuf);
		}
	}
	/*if not found.*/
	pthread_mutex_unlock(&env_mutex);
	return(NULL);
}
