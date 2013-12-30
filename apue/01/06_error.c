/*
 * =====================================================================================
 *
 *       Filename:  06_error.c
 *
 *    Description:  test the error,echo msg according to the errno.
 *
 *        Version:  1.0
 *        Created:  04/18/13 22:25:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */

#include "apue.h"
#include <errno.h>

int main(int argc,char *argv[]){
	printf("Use the printf function\n");
	fprintf(stdout,"Use the fprintf function\n");
	
	fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
	/*set errno for the perror(present error)*/
	errno = ENOENT;
	perror(argv[0]);
	exit(0);
}
