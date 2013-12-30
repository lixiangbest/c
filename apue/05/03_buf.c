/*
 * =====================================================================================
 *
 *       Filename:  03_buf.c
 *
 *    Description:  buf status.
 *    Usage:		./a.out
 *    				./a.out < /etc/motd > std.out 2 > std.err
 *
 *        Version:  1.0
 *        Created:  04/30/13 18:15:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

#if defined(MACOS)
	#define ISSET 1
	#define _IO_UNBUFFERED __SNBF
	#define _IO_LINE_BUF __SLBF
	#define _IO_file_flags __flags
	#define BUFFERSZ(fp) (fp)->_bf._size
#else
	#define ISSET 0
	#define BUFFERSZ(fp) ((fp)->_IO_buf_end - (fp)->_IO_buf_base)
#endif

void pr_stdio(const char *, FILE *);

int main(void){
	FILE *fp;
	printf("defined(MACOS)=%d\n",ISSET);
	fputs("enter any character\n", stdout);
	if(getchar() == EOF){
		err_sys("getchar error");
	}
	fputs("one line to standard error\n", stderr);
	
	pr_stdio("stdin", stdin);
	pr_stdio("stdout", stdout);
	pr_stdio("stderr", stderr);
	/*message of the day.*/
	if((fp = fopen("/etc/motd", "r")) == NULL)
		err_sys("fopen error");
	if(getc(fp) == EOF)
		err_sys("getc error");
	pr_stdio("/etc/motd", fp);
	exit(0);
}

void pr_stdio(const char *name, FILE *fp){
	struct stat buf;
	printf("stream = %s, ", name);
	/*
	* The following is noportable.
	*/
	if(fp->_IO_file_flags & _IO_UNBUFFERED)
		printf("unbuffered");
	else if(fp->_IO_file_flags & _IO_LINE_BUF)
		printf("line buffered");
	else /*if neither of above*/
		printf("fully buffered");
	/*printf(", buffer size = %d\n", BUFFERSZ(fp));*/
	printf(", buffer size = %d\n", fp->_IO_buf_end - fp->_IO_buf_base);
	/*lstat*/
	if(lstat(name,&buf)<0){
		err_ret("%s lstat error!",name);
	}else{
		printf("%s stat blocksize = %ld\n",name,(long int)buf.st_blksize);
	}
}
