/*
 * =====================================================================================
 *
 *       Filename:  03_badexit.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/21/13 03:54:11
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

struct foo{
	int a, b, c, d;
};

/*struct foo foo = {1,2,3,4};*/

void printfoo(const char *s, const struct foo *fp){
	printf("%s",s);
	printf("  structure at 0x%x\n", (unsigned)fp);
	printf("  foo.a = %d\n", fp->a);
	printf("  foo.b = %d\n", fp->b);
	printf("  foo.c = %d\n", fp->c);
	printf("  foo.d = %d\n", fp->d);
}

void *thr_fn1(void *arg){
	struct foo foo = {1,2,3,4};
	printfoo("thread 1:\n", &foo);
	pthread_exit((void*)&foo);

	/*struct foo *foo;
	if((foo = malloc(sizeof(struct foo))) == NULL)
		err_sys("can't allocate memory");
	foo->a = 1,foo->b = 2,foo->c = 3,foo->d = 4;
	printfoo("thread 1:\n", foo);
	pthread_exit((void*)foo);*/
}

void *thr_fn2(void *arg){
	printf("thread 2: ID is %u\n", (unsigned int)pthread_self());
	pthread_exit((void*)0);
}

int main(void){
	int err;
	pthread_t tid1, tid2;
	struct foo *fp;
	void *tret2;

	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if(err!=0){
		err_quit("can't create thread 1: %s\n", strerror(err));
	}
	err = pthread_join(tid1, (void *)&fp);
	if(err!=0){
		err_quit("can't join with thread 1: %s\n", strerror(err));
	}
	printfoo("parent thread 1:\n", fp);
	sleep(1);

	printf("\nparent starting second thread\n");
	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if(err!=0){
		err_quit("can't create thread 2: %s\n", strerror(err));
	}
	err = pthread_join(tid1, &tret2);
	if(err!=0){
		err_quit("can't join with thread 1: %s\n", strerror(err));
	}
	printf("parent thread 2:%d\n", (int)tret2);
	sleep(1);
	exit(0);
}
