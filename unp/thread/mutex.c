/*************************************************************************
	> File Name: mutex.c
	> Description:  mutex.
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月28日 星期六 10时48分18秒
 ************************************************************************/
#include "unp.h"

int sharedi = 0;
void increase_num(void);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(){
	int ret;
	pthread_t thrd1, thrd2, thrd3;

	ret = pthread_create(&thrd1, NULL, (void *)increase_num, NULL);
	ret = pthread_create(&thrd2, NULL, (void *)increase_num, NULL);
	ret = pthread_create(&thrd3, NULL, (void *)increase_num, NULL);

	pthread_join(thrd1, NULL);
	pthread_join(thrd2, NULL);
	pthread_join(thrd3, NULL);
	
	printf("sharedi = %d\n", sharedi);
	return 0;
}

void increase_num(void){
	long i, tmp;
	for(i=0; i<=100000; i++){
		/*lock*/
		if(pthread_mutex_lock(&mutex) != 0){
			perror("pthread_mutex_lock");
			exit(EXIT_FAILURE);
		}
		tmp = sharedi;
		tmp = tmp+1;
		sharedi = tmp;
		/*unlock*/
		if(pthread_mutex_unlock(&mutex) != 0){
			perror("pthread_mutex_unlock");
			exit(EXIT_FAILURE);
		}
	}
}

