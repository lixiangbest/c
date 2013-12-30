/*
 * =====================================================================================
 *
 *       Filename:  mmap.c
 *
 *    Description:  memory map.
 *
 *        Version:  1.0
 *        Created:  06/02/13 16:22:52
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
	char *mapped_mem;
	int flength = 1024;
	void *start_addr = 0;
	
	if((fd = open(argv[1], O_RDWR|O_CREAT, FILE_MODE)) < 0){
		err_sys("open error!");
	}
	flength = lseek(fd, 1, SEEK_END);/*add in the end.*/
	/*add null char, then printf will work normal*/
	if(write(fd, "my dream", 8)!=8){
		err_sys("write error!");
	}
	lseek(fd, 0, SEEK_SET);
	/*PROT_READ allow to read; map_private forbit other process to acess.*/
	mapped_mem = mmap(start_addr, flength, PROT_READ, MAP_PRIVATE, fd, 0);
	/*Use the memory map*/
	printf("%s\n", mapped_mem);
	close(fd);
	munmap(mapped_mem, flength);
	return 0;
}
