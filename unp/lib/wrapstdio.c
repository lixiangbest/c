/*
 * =====================================================================================
 *
 *       Filename:  wrapstdio.c
 *
 *    Description:  Standard I/O wrapper functions.
 *
 *        Version:  1.0
 *        Created:  07/07/13 09:24:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

void Fclose(FILE *fp){
	if(fclose(fp) != 0)
		err_sys("fclose error");
}

FILE *Fdopen(int fd, const char *type){
	FILE *fp;

	if( (fp = fdopen(fd, type)) == NULL)
		err_sys("fdopen error");

	return fp;
}

char *Fgets(char *ptr, int n, FILE *stream){
	char *rptr;

	if( (rptr = fgets(ptr, n, stream)) == NULL && ferror(stream))
		err_sys("fgets error");

	return rptr;
}

FILE *Fopen(const char *filename, const char *mode){
	FILE *fp;

	if( (fp = fopen(filename, mode)) == NULL)
		err_sys("fopen error");

	return fp;
}

void Fputs(const char *ptr, FILE *stream){
	if(fputs(ptr, stream) == EOF)
		err_sys("fputs error");
}
