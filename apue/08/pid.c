/*
 * =====================================================================================
 *
 *       Filename:  pid.c
 *
 *    Description:  pid related functions
 *
 *        Version:  1.0
 *        Created:  05/07/13 23:26:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(){
	pid_t pid;
	printf("getpid = %d\n",getpid());
	printf("getppid = %d\n",getppid());
	printf("getuid = %d\n",getuid());
	printf("geteuid = %d\n",geteuid());
	printf("getgid = %d\n",getgid());
	printf("getegid = %d\n",getegid());

	printf("notice the parent and child buff:");
	if((pid=fork())<0){
		return -1;
	}else if(pid==0){
		printf("look the same!\n");
		fclose(stdout);
		_exit(0);
	}

	if(waitpid(pid,NULL,0) < 0){
		
	}
	exit(0);
}

