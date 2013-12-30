/*
 * =====================================================================================
 *
 *       Filename:  re_lock.c
 *
 *    Description:  record lock
 *
 *        Version:  1.0
 *        Created:  06/01/13 23:19:42
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

void sigint(int signo){
	printf("pid %d catch sigint!\n", getpid());
}

int main(void){
	pid_t pid1, pid2, pid3;
	int fd;
	/*
	struct flock lock_read, lock_write;
	lock_read.l_type = F_RDLCK;
	lock_write.l_type = F_WRLCK;
	lock_read.l_start = lock_write.l_start = 0;
	lock_read.l_whence = lock_write.l_whence = SEEK_SET;
	lock_read.l_len = lock_write.l_len = 0;
	*/

	setbuf(stdout, NULL);/*standard out is nonbuf.*/
	signal_intr(SIGINT, sigint);
	/*
	struct sigaction act, oact;
	act.sa_handler = sigint;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGINT, &act, &oact);*/
	
	/*
	 * Create a file.
	 */
	if((fd = open("lockfile", O_RDWR|O_CREAT, 0666)) < 0){
		err_sys("can't open/create lockfile");
	}

	/*
	 * Read-lock the file.
	 */
	if((pid1 = fork()) < 0){
		err_sys("fork failed");
	}else if(pid1 == 0){/* child */
		if(lock_reg(fd, F_SETLK, F_RDLCK, 0, SEEK_SET, 0) < 0)
			err_sys("child l: can't read-lock file");
		printf("child 1: obtained read lock on file\n");
		pause();
		printf("child 1: exit after pause\n");
		exit(0);
	}else{/*parent*/
		sleep(2);
	}

	/*
	 * Parent continues ... read-lock the file again.
	 */
	if((pid2 = fork()) < 0){
		err_sys("fork failed");
	}else if(pid2 == 0){/* child */
		if(lock_reg(fd, F_SETLK, F_RDLCK, 0, SEEK_SET, 0) < 0)
			err_sys("child 2: can't read-lock file");
		printf("child 2: obtained read lock on file\n");
		pause();
		printf("child 2: exit after pause\n");
		exit(0);
	}else{/*parent*/
		sleep(2);
	}

	/*
	 * Parent continues ... block while trying to write-lock.
	 */
	if((pid3 = fork()) < 0){
		err_sys("fork failed");
	}else if(pid3 == 0){/* child */
		if(lock_reg(fd, F_SETLK, F_WRLCK, 0, SEEK_SET, 0) < 0)
			printf("child 3: can't set write lock: %s\n", strerror(errno));
		
		printf("child 3 about to block in write-lock...\n");
		/*lock block*/
		if(lock_reg(fd, F_SETLKW, F_WRLCK, 0, SEEK_SET, 0) < 0)
			err_sys("child 3: can't write-lock file");

		printf("child 3 returned and got write lock????\n");
		pause();
		printf("child 3: exit after pause\n");
		exit(0);
	}else{/*parent*/
		sleep(2);
	}

	/*
	 * See if a pending write lock will block the next read-lock attempt.
	 */
	if(lock_reg(fd, F_SETLK, F_RDLCK, 0, SEEK_SET, 0) < 0)
		printf("parent: can't read lock: %s\n", strerror(errno));
	else
		printf("parent: obtained additional read lock while "
			" write lock is pending\n");
	
	system("ps -o pid,ppid,pgid,sid,stat,tty,comm");

	printf("killing child 1...\n");
	kill(pid1, SIGINT);
	printf("killing child 2...\n");
	kill(pid2, SIGINT);
	printf("killing child 3...\n");
	kill(pid3, SIGINT);
	sleep(1);/*main process must child process, or can be zombie process.*/
	exit(0);
}
