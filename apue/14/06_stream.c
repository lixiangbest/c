/*
 * =====================================================================================
 *
 *       Filename:  06_stream.c
 *
 *    Description:  stream
 *
 *        Version:  1.0
 *        Created:  05/28/13 08:15:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<stropts.h>
#include<fcntl.h>

int isastream(int fd){
	return(ioctl(fd, I_CANPUT, 0) != -1);
}

int main(int argc, char *argv[]){
	int i, fd;

	for(i = 1;i< argc; i++){
		if((fd = open(argv[i], O_RDONLY)) < 0){
			err_ret("%s: can't open", argv[i]);
			continue;
		}

		if(isastream(fd) == 0){
			err_ret("%s: not a stream", argv[i]);
		}else{
			err_msg("%s: stream device", argv[i]);
		}
	}
	exit(0);
}
