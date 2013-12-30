/*
 * =====================================================================================
 *
 *       Filename:  01_seek.c
 *
 *    Description:  file seek.
 *
 *        Version:  1.0
 *        Created:  04/20/13 17:46:57
 *        Called method:./a.out < /etc/motd(message of the day)
 *        				cat < /etc/motd | ./a.out
 *        				./a.out < /var/spool/cron/FIFO
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<errno.h>

int main(int argc, char *argv[]){
	if(lseek(STDIN_FILENO, 0, SEEK_CUR) == -1){
		printf("cannot seek,%s\n",strerror(errno));
		perror(argv[0]);
	}else{
		printf("%d\n",STDIN_FILENO);
		printf("seek OK\n");
	}
	exit(0);
}

