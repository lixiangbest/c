/*
 * =====================================================================================
 *
 *       Filename:  01_filetype.c
 *
 *    Description:  print the file type.
 *    Usage:		./a.out /etc/passwd /etc /dev/initctl /dev/log /dev/tty \
 *    				> /dev/scsi/host0/bus0/target0/lun0/cd /dev/cdrom
 *
 *        Version:  1.0
 *        Created:  04/22/13 23:11:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

int main(int argc, char *argv[]){
	int i;
	struct stat buf;
	char *ptr;
	for(i=1;i<argc;i++){
		printf("%s: ", argv[i]);
		if(stat(argv[i], &buf)<0){
			err_ret("lstat error");
			continue;
		}
		/*#define,not function*/
		if(S_ISREG(buf.st_mode))
			ptr = "regular";
		else if(S_ISDIR(buf.st_mode))
			ptr = "directory";
		else if(S_ISCHR(buf.st_mode))
			ptr = "character special";
		else if(S_ISBLK(buf.st_mode))
			ptr = "block special";
		else if(S_ISFIFO(buf.st_mode))
			ptr = "FIFO";
		else if(S_ISLNK(buf.st_mode))
			ptr = "symbolic link";
		else if(S_ISSOCK(buf.st_mode))
			ptr = "socket";
		else
			ptr = "** unknown mode **";
		printf("%s\n", ptr);
	}
	exit(0);
}

