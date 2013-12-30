/*
 * =====================================================================================
 *
 *       Filename:  04_changemod.c
 *
 *    Description:  change file mode
 *
 *        Version:  1.0
 *        Created:  04/23/13 23:10:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

int main(void){
	struct stat statbuf;
	
	printf("S_IXGRP=%o,S_IRGRP=%o\n", S_IXGRP, S_IRGRP);
	/*turn on set-group-ID and turn off group-read.execute*/
	if(stat("foo", &statbuf) < 0)
		err_sys("stat error for foo");
	printf("%o\n",statbuf.st_mode);
	if(chmod("foo", (statbuf.st_mode & ~S_IRGRP) | S_ISGID) < 0)
		err_sys("chmod error for foo");

	/* set absolute mode to "rw-r--r--" */
	if(chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
		err_sys("chmod error for bar");

	exit(0);
}

