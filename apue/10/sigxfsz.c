/*
 * =====================================================================================
 *
 *       Filename:  sigxfsz.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/20/13 21:53:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<sys/resource.h>
#include<fcntl.h>
#define BUFFSIZE 100

Sigfunc *signal_intr(int,Sigfunc*);

static void sig_int(int signo){
	printf("catch SIGXFSZ\n");
	return;
}

int main(void){
	int n,w,fd_in,fd_out;
	char buf[BUFFSIZE];
	struct rlimit rptr;

	/*get resource RLIMIT_FSIZE limit*/
	if(getrlimit(RLIMIT_FSIZE, &rptr)<0){
		perror("get limit error");
		exit(0);
	}
	printf("RLIMIT_FSIZE:");
	if(rptr.rlim_cur == RLIM_INFINITY){
		printf("rlim_cur : (infinite)\n");
	}else{
		printf("rlim_cur : %d\n", rptr.rlim_cur);
	}
	if(rptr.rlim_max == RLIM_INFINITY){
		printf("rlim_max : (infinite)\n");
	}else{
		printf("rlim_max : %d\n", rptr.rlim_max);
	}

	/*set RLIMIT_FSIZE, then siganl SIGXFSZ*/
	rptr.rlim_cur = 1024;/*set the max size of created file.*/
	rptr.rlim_max = 1024;
	if(setrlimit(RLIMIT_FSIZE, &rptr) < 0){
		err_sys("setrlimit error.");
	}

	if(signal_intr(SIGXFSZ, sig_int)<0){
		printf("error");
		exit(0);
	}

	if((fd_in = open("warn.html", O_RDWR))<0){
		perror("open error!");
		exit(0);
	}

	fd_out = open("dest.html", O_RDWR|O_CREAT);
	while((n=read(fd_in,buf,BUFFSIZE))>0){
		w = write(fd_out,buf,n);
		printf("write %d; read %d\n", w, n);
		if(w<0){
			perror("write error.");
		}
	}
	if(n<0){
		printf("read error\n");
	}
	exit(0);
}
