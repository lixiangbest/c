/*
 * =====================================================================================
 *
 *       Filename:  system.c
 *
 *    Description:  my system function
 *
 *        Version:  1.0
 *        Created:  05/11/13 16:56:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<sys/wait.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>

int system(const char *cmdstring){/*version without signal handling*/
	pid_t pid;
	int status;
	
	if(cmdstring==NULL){
		return(1);/*always a command processor with UNIX*/
	}

	if((pid=fork())<0){
		status = -1;/*probably out of processes*/
	}else if(pid==0){/*child process*/
		execl("/bin/bash", "bash", "-c", cmdstring, NULL);
		_exit(127);/*execl error*/
	}else{/*parent*/
		while(waitpid(pid, &status, 0) < 0){
			if(errno!=EINTR){
				status = -1;/*error other than EINTR from waitpid()*/
				break;
			}
		}
	}
	return(status);
}

