/*
 * =====================================================================================
 *
 *       Filename:  04_fork.c
 *
 *    Description:  fork twice.
 *
 *        Version:  1.0
 *        Created:  05/08/13 05:37:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<sys/wait.h>

int main(void){
	pid_t pid;
	int status;
	if((pid=fork())<0){
		err_sys("fork error");
	}else if(pid==0){/*first child*/
		if((pid=fork())<0){
			err_sys("fork error");
		}else if(pid>0){
			exit(0);/*parent from second fork==first child*/
		}
		/*
		* We're the second child; our parent becomes init as soon
		* as our real parent calls exit() in the statement above.
		* Here's where we'd continue executing, knowing that when
		* we're done, init will reap our status.
		*/
		sleep(2);
		printf("second child, parent pid = %d\n", getppid());
		exit(0);
	}
	/*wait for first child*/
	printf("super parent:%d;parent:%d,first child:%d\n",getppid(),getpid(),pid);
	if(waitpid(pid, &status, 0)!=pid){
		err_sys("waitpid error");
	}
	printf("wait child status:%d\n",status);
	/* We're the parent (the original process); we continue executing,
	 * knowing that we're not the parent of the second child.
	 */
	exit(0);
}

