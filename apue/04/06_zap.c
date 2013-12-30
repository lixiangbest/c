/*
 * =====================================================================================
 *
 *       Filename:  06_zap.c
 *
 *    Description:  utime sample
 *
 *        Version:  1.0
 *        Created:  04/24/13 05:40:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<fcntl.h>
#include<utime.h>

int main(int argc, char *argv[]){
	int i, fd;
	struct stat statbuf;
	struct utimbuf timebuf;
	for(i=1;i<argc;i++){
		/*fetch current times*/
		if(stat(argv[i], &statbuf) < 0){
			err_ret("%s: stat error", argv[i]);
			continue;
		}
		/*truncate*/
		if((fd = open(argv[i], O_RDWR | O_TRUNC) < 0)){
			err_ret("%s: open error", argv[i]);
			continue;
		}
		close(fd);
		printf("%s,atime=%d,utime=%d\n",argv[i],timebuf.actime,timebuf.modtime);
		/*file access time*/
		timebuf.actime = statbuf.st_atime;
		/*file modification time, not i node status change time.*/
		timebuf.modtime = statbuf.st_mtime;
		/*reset times*/
		if(utime(argv[i], &timebuf) < 0){
			err_ret("%s: utime error", argv[i]);
			continue;
		}
	}
	exit(0);
}

