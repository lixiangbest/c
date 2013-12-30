/*
 * =====================================================================================
 *
 *       Filename:  select1.c
 *
 *    Description:  select usage.
 *
 *        Version:  1.0
 *        Created:  06/29/13 18:47:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<sys/stat.h>
#include<fcntl.h>
#include<assert.h>
#include<sys/time.h>

int main(){
	int keyboard;
	int ret,i;
	char c;
	fd_set readfd;
	struct timeval timeout;
	keyboard = open("/dev/tty", O_RDONLY|O_NONBLOCK);
	assert(keyboard>0);
	while(1){
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		FD_ZERO(&readfd);
		FD_SET(keyboard, &readfd);
		if((ret = select(keyboard+1, &readfd, NULL, NULL, &timeout)) < 0)
			err_sys("select error");
		/*time out when ret = 0*/
		if(ret == 0) printf("time out\n");
		if(FD_ISSET(keyboard,&readfd)){
			i = read(keyboard,&c,1);
			if(c=='\n') continue;
			printf("input is %c\n", c);
			if(c=='q') break;
		}
	}
	return 0;
}

