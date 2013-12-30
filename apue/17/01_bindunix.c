/*
 * =====================================================================================
 *
 *       Filename:  01_bindunix.c
 *
 *    Description:  bind unix domain socket path.
 *
 *        Version:  1.0
 *        Created:  06/13/13 21:58:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<sys/socket.h>
#include<sys/un.h>

int main(void){
	int fd, size;
	struct sockaddr_un un;

	un.sun_family = AF_UNIX;
	strcpy(un.sun_path, "foo.socket");
	if((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
		err_sys("socket failed");
	/*get the member offset in the struct.*/
	size = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);

	printf("offset sun_path:%d\n", (int)&((struct sockaddr_un *)0)->sun_path);
	printf("offset size:%d, struct sockaddr_un size:%d\n", size, sizeof(un));
	printf("offset family:%d, path:%d\n", offsetof(struct sockaddr_un, sun_family), offsetof(struct sockaddr_un, sun_path));
	printf("sun_path strlen:%d, sizeof:%d\n", strlen(un.sun_path), sizeof(un.sun_path));
	printf("sun_family sizeof:%d\n", sizeof(un.sun_family));

	/*if(bind(fd, (struct sockaddr *)&un, size) < 0)*/
	if(bind(fd, (struct sockaddr *)&un, sizeof(un)) < 0)
		err_sys("bind failed");
	printf("UNIX domain socket bound\n");

	exit(0);
}
