/*************************************************************************
	> File Name: sem.c
	> Description: semaphore
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月28日 星期六 11时39分10秒
 ************************************************************************/
#include "unp.h"
#include<semaphore.h>

#define MAXSIZE 10
int stack[MAXSIZE];
int size = 0;
sem_t sem;

//produce
void provide_data(void){
	int i;
	for(i=0; i<MAXSIZE; i++){
		stack[i] = i;
		sem_post(&sem);//sem add
	}
}

//consume
void handle_data(void){
	int i;
	while( (i = size++) < MAXSIZE ){
		sem_wait(&sem);
		printf("plus: %d X %d = %d\n", stack[i], stack[i], stack[i]*stack[i]);
		sleep(1);
	}
}

int main(void){
	pthread_t provider, handler;
	
	sem_init(&sem, 0, 0);//init sem
	pthread_create(&provider, NULL, (void*)handle_data, NULL);
	pthread_create(&handler, NULL, (void*)provide_data, NULL);
	
	pthread_join(provider, NULL);
	Pthread_join(handler, NULL);
	
	sem_destroy(&sem);//destroy sem
	return 0;
}

