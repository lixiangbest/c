/*
 * =====================================================================================
 *
 *       Filename:  pipestdin.c
 *
 *    Description:  pipe stdin, make fifo.
 *    		Usage:  ./pipestdin
 *    				cat > fifotmp
 *
 *        Version:  1.0
 *        Created:  06/29/13 16:39:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

int main(int argc, char**argv){
	int i,fd,fd1;
	char **ar = argv;
	char *fifo = "fifotmp";
	char line[5];
	for(i=0;i<argc;i++){
		printf("argc=%d,argv=%s,ar=%s\n", i, argv[i],*ar);
		ar++;
	}
	
	/*
	if(mkfifo(fifo, S_IRWXU | S_IRWXG | S_IRWXO)<0)
		err_sys("mkfifo error");
	*/

	/*fd block until other program write to the fifo.*/
	if((fd = open(fifo, O_RDONLY)) < 0)
		err_sys("open error");
	
	printf("open fifo\n");
	/*dup2(0, fd1);*/
	dup2(fd, 0);/*0 is the file descriptor of stdin*/

	while(fgets(line, 1024, stdin)!=NULL)
	/*while(read(fd1, line, 5))*/
		printf("I got this: %s\n", line);

	/*fputs(fgets(line,5,stdin),stdout);*/
	return 0;
}

