/*************************************************************************
	> File Name: no_mutex.c
	> Description: no mutex 
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月28日 星期六 09时54分50秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int sharedi = 0;

void increase_num(void);

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
		tmp = sharedi;
		tmp = tmp + 1;
		sharedi = tmp;
	}
}

