/*
 * =====================================================================================
 *
 *       Filename:  03_fsess.c
 *
 *    Description:   
 *
 *        Version:  1.0
 *        Created:  05/13/13 23:21:59
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
#include<sys/types.h>
#include<sys/wait.h>

int main(void){
	pid_t pid;
	/*print the parent pid,pgid*/
	printf("father's pid is %d,pgid is %d\n",getpid(),getpgid(0));
	if((pid=fork())<0){/*fork child process*/
		printf("fork error\n");
		exit(1);
	}else if(pid==0){/*child*/
		/*print the child pid,pgid*/
		printf("before set, child's pid is %d,pgid is %d\n", getpid(), getpgid(0));
		if(setsid() < 0){/*create new session*/
			printf("setsid error\n");
			exit(-1);
		}
		printf("sid is %d\n", getsid(0));/*see session id*/
		/*check child has controll termination or not.*/
		if(open("/dev/tty", O_RDWR) < 0){
			printf("open error\n");
			exit(1);
		}
		exit(0);
	}
	if(waitpid(pid,NULL,0) < 0){
		err_sys("wait error");
	}
	/*check parent has controll termination or not.*/
	if(open("/dev/tty", O_RDWR) < 0){
		printf("open error\n");
		exit(1);
	}else{
		printf("father open ok\n");
	}
	exit(0);
}

