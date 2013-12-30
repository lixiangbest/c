/*
 * =====================================================================================
 *
 *       Filename:  prexit.c
 *
 *    Description:  print the child process status
 *
 *        Version:  1.0
 *        Created:  05/08/13 03:13:12
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

void pr_exit(int status){
	if(WIFEXITED(status)){
		printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
	}else if(WIFSIGNALED(status)){
		printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
			WCOREDUMP(status)?" (core file generated)":"");
#else
			"");
#endif
	}else if(WIFSTOPPED(status)){
		printf("child stopped, signal number = %d\n", WSTOPSIG(status));
	}
}

