/*
 * =====================================================================================
 *
 *       Filename:  08_devzero.c
 *
 *    Description:  /dev/zero char device.
 *
 *        Version:  1.0
 *        Created:  06/06/13 02:36:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<fcntl.h>
#include<sys/mman.h>

#define NLOOPS 1000
#define SIZE sizeof(long) /*size of shared memory area*/

static int update(long *ptr){
	return((*ptr)++);/*return value before increment*/
}

int main(void){
	int fd, i, counter;
	pid_t pid;
	void *area;
	/*
	if((fd = open("/dev/zero", O_RDWR)) < 0)
		err_sys("open error");
	*/
	/*if((area = mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)*/
	if((area = mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0)) == MAP_FAILED)
		err_sys("mmap error");
	close(fd);/*can close /dev/zero now that it's mapped*/

	/*
	int *m = &i;
	i = 2;
	printf("m=%d\n", *m);
	printf("update m=%d\n", update(m));
	printf("after update m=%d\n", *m);
	printf("NLOOPS = %ld\n", NLOOPS);
	exit(0);
	*/

	printf("initialize area:%d\n", *(int*)area);
	TELL_WAIT();

	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid > 0){/*parent*/
		for(i = 0; i < NLOOPS; i+=2){
			if((counter = update((long*)area)) != i)
				err_quit("parent: expected %d, got %d", i, counter);
			printf("parent i = %d, counter = %d\n", i, counter);
			TELL_CHILD(pid);
			WAIT_CHILD();
		}
	}else{/*child*/
		for(i = 1; i < NLOOPS+1; i+=2){
			WAIT_PARENT();
			if((counter = update((long *)area)) != i)
				err_quit("child: expected %d, got %d", i, counter);
			printf("child i = %d, counter = %d\n", i, counter);
			TELL_PARENT(getppid());
		}
	}
	exit(0);
}
