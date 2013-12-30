/*
 * =====================================================================================
 *
 *       Filename:  child.c
 *
 *    Description:  fork usage.
 *
 *        Version:  1.0
 *        Created:  05/08/13 00:35:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

int main(void){
	int m;
	char str[10];
	printf("print times!\n");
	pid_t pid = fork();
	/*child process*/
	if(pid==0){
		int j;
		for(j=0;j<5;j++){
			printf("child: %d\n", j);
			sleep(1);
		}
		strcpy(str,"Child");
		m = 0;
	}else if(pid>0){/*parent*/
		int i;
		for(i=0;i<5;i++){
			printf("parent:%d\n",i);
			sleep(1);
		}
		strcpy(str,"Parent");
		m = 1;
	}else{
		fprintf(stderr,"can't fork,error %d\n",errno);
		exit(1);
	}
	printf("%d,%s m = %d\n",getpid(),str,m);
	printf("This is the end!\n");
	return 0;
}

