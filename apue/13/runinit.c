/*
 * =====================================================================================
 *
 *       Filename:  init.c
 *
 *    Description:  daemon init.
 *
 *        Version:  1.0
 *        Created:  05/26/13 15:45:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<syslog.h>
#include<fcntl.h>
#include<sys/resource.h>

void daemonize(void){
	pid_t pid;

	/*Become a session leader to lose controlling TTY*/
	if((pid = fork()) < 0){
		perror("cant' fork");
		exit(1);
	}else if(pid != 0){/*parent*/
		exit(0);
	}
	setsid();

	/*Change the current working directory to the root so we won't
	 *prevent file systems from being unmounted.*/
	if(chdir("/") < 0){
		perror("can't change directory to /");
		exit(1);
	}

	/*Attach file descriptors 0, 1, and 2 to /dev/null.*/
	close(0);
	open("/dev/null", O_RDWR);
	dup2(0, 1);
	dup2(0, 2);
}

int main(void){
	daemonize();
	while(1){
		sleep(1);
	}
}
