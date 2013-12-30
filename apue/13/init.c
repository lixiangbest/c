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

void daemonize(const char *cmd){
	int i, fd0, fd1, fd2;
	pid_t pid;
	struct rlimit rt;
	struct sigaction sa;
	sigset_t waitmask;


	/*clear file creation mask*/
	umask(0);

	/*Get maximum number of file descriptors.*/
	if(getrlimit(RLIMIT_NOFILE, &rt) < 0)
		err_quit("%s: can' get file limit", cmd);

	/*Become a session leader to lose controlling TTY*/
	if((pid = fork()) < 0){
		err_quit("%s: cant' fork", cmd);
	}else if(pid != 0){/*parent*/
		exit(0);
	}
	setsid();
	
	/*
	 * Ensure future opens won't allocate controlling TTYs
	 */
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if(sigaction(SIGHUP, &sa, NULL) < 0){
		err_quit("%s: can't ignore SIGHUP");
	}
	if((pid = fork()) < 0){
		err_quit("%s: can't fork", cmd);
	}else if(pid != 0){/*parent*/
		exit(0);
	}
	/*setsid();*//*setsid must be run after ignoring SIGHUP, avoid process exit for the system send SIGHUP signal.*/

	/*Change the current working directory to the root so we won't
	 *prevent file systems from being unmounted.*/
	if(chdir("/") < 0)
		err_quit("%s: can't change directory to /");

	/*Close all open file descriptors.*/
	if(rt.rlim_max == RLIM_INFINITY)
		rt.rlim_max = 1024;
	for(i=0;i<rt.rlim_max;i++)
		close(i);

	/*Attach file descriptors 0, 1, and 2 to /dev/null.*/
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	/*Initialize the log file.*/
	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if(fd0 != 0 || fd1 != 1 || fd2 !=2){
		syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
		exit(1);
	}

	/*I add three line code.*/
	/*sigemptyset(&waitmask);*//*ignore the singal SIGHUP*/
	/*
	if(sigsuspend(&waitmask) != -1){
		err_sys("sigsuspend error");
	}
	*/
}
