/*
 * =====================================================================================
 *
 *       Filename:  10_devrdev.c
 *
 *    Description:  dev read device.
 *			usage: ./a.out / /home/sar /dev/tty[01]
 *        Version:  1.0
 *        Created:  04/24/13 15:43:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#ifdef SOLARIS
#include <sys/mkdev.h>
#endif

int main(int argc, char *argv[]){
	int i;
	struct stat buf;
	
	for(i=1;i<argc;i++){
		printf("%s: ", argv[i]);
		if(stat(argv[i], &buf) < 0){
			err_ret("stat error");
			continue;
		}

		printf("dev = %d/%d", major(buf.st_dev), minor(buf.st_dev));
		/*S_? is macro, not a function*/
		if(S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode)){
			printf(" (%s) rdev = %d/%d", (S_ISCHR(buf.st_mode))?"character":"block",major(buf.st_rdev),minor(buf.st_rdev));
		}
		printf("\n");
	}
	exit(0);
}

