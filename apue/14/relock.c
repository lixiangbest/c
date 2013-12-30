/*
 * =====================================================================================
 *
 *       Filename:  relock.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/02/13 14:37:04
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
#include<errno.h>

void sig_handler(int signo){

}

int main(void){
	int    fd;
	pid_t  pid1, pid2, pid3;

	/* intialise the flock struct for fcntl to lock files */
	struct flock lock_read, lock_write;
	lock_read.l_type = F_RDLCK;
	lock_write.l_type = F_WRLCK;
	lock_read.l_start = lock_write.l_start = 0;
	lock_read.l_whence = lock_write.l_whence = SEEK_SET;
	lock_read.l_len = lock_write.l_len = 0;

	/* intialise the sigaction struct for sigaction function */
	struct sigaction act, oact;
	act.sa_handler = sig_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	sigaction(SIGINT, &act, &oact);
	/*create a file.*/
	if((fd = open("relockfile", O_RDWR | O_CREAT, 0666)) < 0)
		err_sys("can't open/creat lockfile");

	/*read-lock the file.*/
	if((pid1 = fork()) < 0)
		err_sys("fork error");
	else if(pid1 == 0){
		if (fcntl(fd, F_SETLK, &lock_read) < 0)
			err_sys("child 1: can't lock lockfile");
		printf("child 1: obtained read lock on lockfile\n");
		pause();
		printf("child 1: exit after pause\n");
		exit(0);
	} else {
		sleep(2);
	}

	if((pid2 = fork()) < 0)
		err_sys("fork failed");
	else if(pid2 == 0){
		if(fcntl(fd, F_SETLK, &lock_read) < 0)
			err_sys("child 2: can't lock lockfile");
		printf("child 2: obtained  read lock on lockfile\n");
		pause();
		printf("child 2: exit after pause\n");
		exit(0);
	}else{
		sleep(2);
	}

	if((pid3 = fork()) < 0)
		err_sys("fork failed");
	else if(pid3 == 0){
		if(fcntl(fd, F_SETLK, &lock_write) < 0)
			printf("child 3: can't set write lock: %s\n", strerror(errno));
		printf("child 3: about to block in write lock...\n");
		if(fcntl(fd, F_SETLKW, &lock_write) < 0)
			err_sys("child 3: can't write-lock file");
		pause();
		printf("child 3: exit after pause\n");
		exit(0);
	}else{
		sleep(2);
	}

	if(fcntl(fd, F_SETLK, &lock_read) < 0)
		printf("parent: can't set read lock: %s\n", strerror(errno));
	else
		printf("parent: obtained additional read lock while read lock is pending\n");
	printf("killing child 1...\n");
	kill(pid1, SIGINT);
	printf("killing child 2...\n");
	kill(pid2, SIGINT);
	printf("killing child 3...\n");
	kill(pid3, SIGINT);
	sleep(1);
	exit(0);
}
