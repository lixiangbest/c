/*
 * =====================================================================================
 *
 *       Filename:  05_tempnam.c
 *
 *    Description:  tempnam function usage.
 *    Usage:		./a.out /home/sar TEMP
 *    				./a.out " " PEX
 *
 *        Version:  1.0
 *        Created:  04/30/13 21:53:01
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
	char name[] = "template-XXXXXX";
	char buf[MAXLINE];
	int fd;
	printf("P_tmpdir=%s\n",P_tmpdir);
	fd = mkstemp(name);/*mkstemp*/
	printf("fd=%d,name=%s\n",fd,name);
	write(fd,name,sizeof(name));
	unlink(name);
	printf("0=%s\n",0);
	lseek(fd,0,SEEK_SET);
	if(read(fd,buf,MAXLINE)<0){
		err_sys("read %s error!",name);
	}
	printf("after unlink,get file content:%s\n",buf);
	
	if(argc!=3)
		err_quit("usage: a.out <directory> <prefix>");
	printf("%s\n", tempnam(argv[1][0]!=' '?argv[1]:NULL,argv[2][0]!=' '?argv[2]:NULL));
	exit(0);
}

