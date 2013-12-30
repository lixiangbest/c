/*
 * =====================================================================================
 *
 *       Filename:  writen.c
 *
 *    Description:	write number
 *
 *        Version:  1.0
 *        Created:  05/28/13 15:39:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */


#include "apue.h"

/*Write "n" bytes to a descriptor*/
ssize_t writen(int fd,const void *ptr, size_t n){
	size_t nleft;
	ssize_t nwritten;

	nleft = n;
	while(nleft > 0){
		if((nwritten = write(fd, ptr, nleft)) < 0){
			if(nleft == n){
				return -1;/*error, return -1*/
			}else{
				break;/*error, return amount written so far*/
			}
		}else if(nwritten == 0){
			break;/*EOF*/
		}
		nleft -= nwritten;
		ptr += nwritten;
	}
	return(n - nleft);/*return >= 0*/
}
