/*************************************************************************
	> File Name: simple.c
	> Description: simple thread hello world.
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月28日 星期六 03时35分39秒
 ************************************************************************/
#include "unp.h"

void print_message_function(void *ptr);

int count = 0;

int main(){
	int tmp1, tmp2;
	void *retval;
	pthread_t thread1, thread2;
	char *message1 = "thread1";
	char *message2 = "thread2";
	int ret_thrd1, ret_thrd2;
	
	ret_thrd1 = pthread_create(&thread1, NULL, (void *)&print_message_function, (void *)message1);
	ret_thrd2 = pthread_create(&thread2, NULL, (void *)&print_message_function, (void *)message2);
	//sleep(5);
	//success to create thread
	if(ret_thrd1 != 0){
		printf("fail to create thread1!\n");
	}else{
		printf("success to create thread1:0x%x!\n", thread1);
	}

	if(ret_thrd2 != 0){
		printf("fail to create thread2!\n");
	}else{
		printf("success to create thread2:0x%x!\n", thread2);
	}
	
	//pthread_join return val is 0
	tmp1 = pthread_join(thread1, &retval);
	printf("thread1 return value(retval) is %d\n", (int)retval);
	printf("thread1 return value(tmp) is %d\n", tmp1);
	if(tmp1 != 0){
		printf("cannot join with thread1\n");
	}
	printf("thread1 end\n");

	//pthread_join return val is 0
	tmp2 = pthread_join(thread2, &retval);
	printf("thread2 return value(retval) is %d\n", (int)retval);
	printf("thread2 return value(tmp) is %d\n", tmp2);
	if(tmp2 != 0){
		printf("cannot join with thread2\n");
	}
	printf("thread2 end\n");

	printf("thread count = %d\n", count);
	return 0;
}

void print_message_function(void *ptr){
	int i = 0;
	//sleep(2);
	for(; i<5; i++){
		printf("%s:%d\n", (char *)ptr, i);
	}
	for(i=0; i<2000000; i++){
		count++;
	}
}

