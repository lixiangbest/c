/*
 * =====================================================================================
 *
 *       Filename:  lockfile.c
 *
 *    Description:  add write lock on the fd file.
 *
 *        Version:  1.0
 *        Created:  05/26/13 18:42:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<unistd.h>
#include<fcntl.h>

int lockfile(int fd){
	struct flock fl;

	fl.l_type = F_WRLCK;
	fl.l_start = 0;
	fl.l_whence = SEEK_SET;
	fl.l_len = 0;
	return(fcntl(fd, F_SETLK, &fl));
}

