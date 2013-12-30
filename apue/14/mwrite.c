/*
 * =====================================================================================
 *
 *       Filename:  mwrite.c
 *
 *    Description:  memory write.
 *
 *        Version:  1.0
 *        Created:  06/02/13 16:43:46
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
#include<sys/mman.h>

int main(int argc, char **argv){
	int fd;
	char *mapped_mem, *p=NULL;
	int flength = 1024;
	void *start_addr = 0;
	
	if((fd = open(argv[1], O_RDWR|O_CREAT, FILE_MODE)) < 0){
		err_sys("open error!");
	}
	flength = lseek(fd, 1, SEEK_END);/*add in the end.*/
	/*add null char, then printf will work normal*/
	if(write(fd, "\0", 1)!=1){
		err_sys("write error!");
	}
	lseek(fd, 0, SEEK_SET);
	/*start_addr = 0x80000;*/
	/*PROT_READ allow to read; map_private forbit other process to acess.*/
	mapped_mem = mmap(start_addr, flength, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	/*Use the memory map*/
	printf("%s\n", mapped_mem);/*to work well.argc[1] could be a text file.*/
	/*map.txt must start with Hello text, or p is 0*/
	while((p = strstr(mapped_mem, "H"))){/*modify this text content.*/
		memcpy(p, "Linux is my favourite", 21);
		p+=5;
	}
	close(fd);
	munmap(mapped_mem, flength);
	return 0;
}

