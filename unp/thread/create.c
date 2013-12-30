/*************************************************************************
	> File Name: create.c
	> Description: thread create 
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月28日 星期六 04时49分08秒
 ************************************************************************/
#include "unp.h"

/*print x to stderr, don't use parameter, no return value*/
void *print_xs(void *unused){
	while(1){
		fputc('x', stderr);
		//sleep(1);
	}
	return NULL;
}

int main(){
	pthread_t thread_id;
	/*new thread. thread run 'print_xs' function.*/
	pthread_create(&thread_id, NULL, *print_xs, NULL);
	/*output o to stderr*/
	while(1){
		fputc('o', stderr);
		//sleep(1);
	}

	return 0;
}

