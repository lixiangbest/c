/*
 * =====================================================================================
 *
 *       Filename:  07_mcopy.c
 *
 *    Description:  memory map copy
 *
 *        Version:  1.0
 *        Created:  06/01/13 10:01:11
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
#include<signal.h>
#include<sys/mman.h>

static void sig_h(int signo){
	if(signo==SIGSEGV){
		printf("catch SIGSEGV\n");
	}else if(signo==SIGBUS){
		printf("catch SIGBUS\n");
	}
}

int main(int argc, char *argv[]){
	int fdin, fdout;
	void *src, *dst;
	struct stat inbuf,outbuf;

	if(signal(SIGSEGV, sig_h)<0){
		err_sys("SIGSEGV error\n");
	}
	if(signal(SIGBUS, sig_h)<0){
		err_sys("SIGSEGV\n");
	}

	if(argc!=3){
		err_quit("usage: %s <fromfile> <tofile>", argv[0]);
	}

	if((fdin = open(argv[1], O_RDONLY)) < 0)
		err_sys("can't open %s for reading", argv[1]);

	/*if((fdout = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, FILE_MODE)) < 0)*/
	if((fdout = open(argv[2], O_RDWR|O_CREAT, FILE_MODE)) < 0)
		err_sys("can't creat %s for writing", argv[2]);

	if(fstat(fdin, &inbuf) < 0){/*need size of input file*/
		err_sys("fstat error");
	}

	/*set size of output file*/
	printf("%s st_size: %d\n", argv[1], (int)inbuf.st_size);
	if(lseek(fdout, inbuf.st_size-1, SEEK_END) == -1)
		err_sys("lseek error");

	if(fstat(fdout, &outbuf) < 0){/*need size of input file*/
		err_sys("fstat error");
	}
	printf("%s st_size: %d\n", argv[2], (int)outbuf.st_size);
	if(write(fdout, "", 1) != 1)
		err_sys("write error");
	
	/*input file map*/
	if((src = mmap(0, inbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0)) == MAP_FAILED)
		err_sys("mmap error for input");
	close(fdin);/*close the input file.*/

	/*input file map*/
	if((dst = mmap(0, inbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fdout, (int)outbuf.st_size)) == MAP_FAILED)
		err_sys("mmap error for output");

	memcpy(dst, src, inbuf.st_size);/*does the file copy*/
	/*kill(getpid(), SIGBUS);*/
	kill(getpid(), SIGSEGV);
	printf("memory copy finish!\n");
	exit(0);
}

