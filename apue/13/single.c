/*
 * =====================================================================================
 *
 *       Filename:  single.c
 *
 *    Description:  already_running
 *
 *        Version:  1.0
 *        Created:  05/26/13 18:33:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<unistd.h>
#include<stdlib.h>
#include<syslog.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<stdio.h>
#include<sys/stat.h>

#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

extern int lockfile(int);

int already_running(void){
	int fd;
	char buf[16];
	/*open lock file.when created files, LOCKMODE is effect.*/
	fd = open(LOCKFILE, O_RDWR|O_CREAT, LOCKMODE);
	if(fd < 0){
		syslog(LOG_ERR, "can't open %s: %s", LOCKFILE, strerror(errno));
		exit(1);
	}
	/*attempt to lock the fd*/
	if(lockfile(fd) < 0){
		/*if no authority or resource can't use.*/
		if(errno == EACCES || errno == EAGAIN){
			close(fd);
			exit(1);
		}
		syslog(LOG_ERR, "can't lock %s: %s", LOCKFILE, strerror(errno));
		exit(1);
	}

	ftruncate(fd, 0);
	sprintf(buf, "%ld", (long)getpid());
	write(fd, buf, strlen(buf)+1);
	return(0);
}

