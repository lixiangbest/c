/*
 * =====================================================================================
 *
 *       Filename:  readn.c
 *
 *    Description:  read number
 *
 *        Version:  1.0
 *        Created:  05/28/13 15:32:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

/*Read "n" bytes from a descriptor*/
ssize_t readn(int fd, void *ptr, size_t n){
	size_t nleft;
	ssize_t nread;

	nleft = n;
	while(nleft > 0){
		if((nread = read(fd, ptr, nleft)) < 0){
			if(nleft == n){
				return -1;/*error, return -1*/
			}else{
				break;
			}
		}else if(nread == 0){
			break;/*EOF*/
		}
		nleft -= nread;
		ptr += nread;
	}
	return(n - nleft);/*return >= 0*/
}

