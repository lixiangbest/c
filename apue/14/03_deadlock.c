/*
 * =====================================================================================
 *
 *       Filename:  03_deadlock.c
 *
 *    Description:  dead lock test
 *
 *        Version:  1.0
 *        Created:  05/28/13 01:45:26
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

static void lockabyte(const char *name, int fd, off_t offset){
	if(writew_lock(fd, offset, SEEK_SET, 1) < 0){
		err_sys("errno:%d, %s: writew_lock error", errno, name);
	}
	printf("%s: got the lock, byte %ld\n", name, offset);
}

int main(void){
	int fd;
	pid_t pid;
	
	/*create a file and write two*/
	if((fd = creat("templock", FILE_MODE)) < 0)
		err_sys("create error");
	if(write(fd, "abcdef", 6) != 6)
		err_sys("write error");

	TELL_WAIT();
	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid==0){/*child*/
		lockabyte("child", fd, 0);
		TELL_PARENT(getppid());
		WAIT_PARENT();
		lockabyte("child", fd, 1);
	}else{/*parent*/
		lockabyte("parent", fd, 1);
		TELL_CHILD(pid);
		WAIT_CHILD();
		lockabyte("parent", fd, 0);
	}
	exit(0);
}
