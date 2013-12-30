/*
 * =====================================================================================
 *
 *       Filename:  treadline1.c
 *
 *    Description:  test readline function
 *
 *        Version:  1.0
 *        Created:  07/13/13 19:11:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

/*Painfully slow version -- example only*/
ssize_t readline(int fd, void *vptr, size_t maxlen){
	ssize_t n, rc;
	char c, *ptr;

	ptr = vptr;
	for(n=1; n<maxlen; n++){
again:
		if( (rc = read(fd, &c, 1)) == 1){
			*ptr++ = c;
			if(c == '\n')	break;/*newline is stored, like fgets()*/
		}else if(rc == 0){
			*ptr = 0;
			return(n-1);/*EOF, n-1 bytes were read*/
		}else{
			if(errno == EINTR)
				goto again;
			return -1;/*error, errno set by read()*/
		}
	}
	*ptr = 0;/*null terminate like fgets()*/
	return n;
}
/*end readline*/

ssize_t Readline(int fd, void *ptr, size_t maxlen){
	ssize_t n;

	if( (n = readline(fd, ptr, maxlen)) < 0)
		err_sys("readline error");
	return n;
}

int main(int argc, char **argv){
	int count = 0;
	ssize_t n;
	char recvline[MAXLINE];

	while( (n = readline(STDIN_FILENO, recvline, MAXLINE)) > 0)
		count++;/*read line count.*/
	printf("%d lines\n", count);
	return 0;
}

