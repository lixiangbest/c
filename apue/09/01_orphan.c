/*
 * =====================================================================================
 *
 *       Filename:  01_orphan.c
 *
 *    Description:  orphan process group.
 *
 *        Version:  1.0
 *        Created:  05/12/13 23:40:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<errno.h>

static void sig_hup(int signo){
	printf("SIGHUP received, pid = %d\n", getpid());
}

static void pr_ids(char *name){
	printf("%s: pid = %d, ppid = %d, pgrp = %d, tpgrp = %d\n", name, getpid(), getppid(), getpgrp(), tcgetpgrp(STDIN_FILENO));
	fflush(stdout);
}

int main(void){
	char c;
	pid_t pid;
	pr_ids("parent");/*parent id*/
	if((pid=fork()) < 0){
		err_sys("fork error");
	}else if(pid > 0){/*parent*/
		sleep(5);/*sleep to let child stop itself*/
		exit(0);/*then parent exits*/
	}else{
		pr_ids("child");
		signal(SIGHUP, sig_hup);/*establish signal handler*/
		kill(getpid(), SIGTSTP);/*stop ourself,hang up process*/
		pr_ids("child");/*prints only if we're continued*/
		if(read(STDIN_FILENO, &c, 1) != 1){
			printf("read error from controlling TTY, errno = %d\n", errno);
		}else
			printf("c=%c\n",c);
		exit(0);
	}
}

