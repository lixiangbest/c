/*
 * =====================================================================================
 *
 *       Filename:  lockreg.c
 *
 *    Description:  lock reg.
 *
 *        Version:  1.0
 *        Created:  05/27/13 23:27:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include <fcntl.h>

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len){
	struct flock lock;
	lock.l_type = type;/*F_RDLCK, F_WRLCK, F_UNLCK*/
	lock.l_start = offset;/*byte offset, relative to l_whence*/
	lock.l_whence = whence;/*SEEK_SET, SEEK_CUR, SEEK_END*/
	lock.l_len = len;/*#bytes (0 means to EOF)*/

	return(fcntl(fd, cmd, &lock));
}

