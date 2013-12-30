/*
 * =====================================================================================
 *
 *       Filename:  writen.c
 *
 *    Description:  write for number bytes.
 *
 *        Version:  1.0
 *        Created:  07/13/13 18:45:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

/*write 'n' bytes from a descriptor.*/
ssize_t writen(int fd, const void *vptr, size_t n){
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;

	ptr = vptr;
	nleft = n;
	while(nleft > 0){
		if( (nwritten = write(fd, ptr, nleft)) <= 0){
			if(nwritten < 0 && errno == EINTR)
				nwritten = 0;/*and call write() again*/
			else
				return -1;/*error*/
		}
		
		nleft -= nwritten;/*left bytes to write.*/
		ptr += nwritten;
	}
	return(n);/*return >= 0*/
}
/*end readn*/

void Writen(int fd, void *ptr, size_t nbytes){

	if(writen(fd, ptr, nbytes) != nbytes)
		err_sys("writen error");
}

