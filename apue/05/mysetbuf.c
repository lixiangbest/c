/*
 * =====================================================================================
 *
 *       Filename:  mysetbuf.c
 *
 *    Description:  setvbuf to setbuf
 *
 *        Version:  1.0
 *        Created:  04/30/13 22:48:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<stdlib.h>
#ifndef BUFSIZ
#define isset 0
#define BUFSIZ 1024
#else
#define isset 1
#endif

void pr_stdio(const char *name, FILE *fp);
void mybuf(FILE *fp, char *buf);

int main(int argc,char* argv[]){
	char buf[BUFSIZ];
	FILE *fp;
	printf("output = %d\n",printf(""));
	printf("BUFSIZ %d,isset = %d\n",BUFSIZ,isset);
	if(-1){
		printf("-1 is true!");
	}else{
		printf("-1 is false!");
	}
	if(argc!=2){
		printf("error argc must be 2!");
		exit(1);
	}
	if((fp=fopen(argv[1],"w"))){
		mybuf(stderr,buf);
		pr_stdio("stderr",stderr);

		mybuf(stdin,buf);
		pr_stdio("stdout",stdout);
		
		mybuf(fp,NULL);
		pr_stdio(argv[1],fp);

		mybuf(fp,buf);
		pr_stdio(argv[1],fp);
	}
	fclose(fp);
	exit(0);
}

void mybuf(FILE *fp, char *buf){
	if(buf==NULL){
		if(setvbuf(fp,buf,_IONBF,BUFSIZ)){
			perror("setvbuf error");
			exit(-1);
		}
		printf("no buf\n");
	}else{
		if(fp==stderr){
			if(setvbuf(fp,buf,_IONBF,BUFSIZ)){
				perror("setvbuf error");
				exit(-1);
			}
			printf("no buf\n");
		}
		else if(fp==stdin||fp==stdout){
			if(setvbuf(fp,buf,_IOLBF,BUFSIZ)){
				perror("setvbuf error");
				exit(-1);
			}
			printf("line buf\n");
		}else{
			if(setvbuf(fp,buf,_IOFBF,BUFSIZ)){
				perror("setvbuf error");
				exit(-1);
			}
			printf("full buf\n");
		}
	}
}

void pr_stdio(const char *name, FILE *fp){
	printf("stream = %s.", name);
	printf("fp->_IO_file_flags=%o.",fp->_IO_file_flags);
	if(fp->_IO_file_flags & _IO_UNBUFFERED){
		printf("unbuffered,_IO_UNBUFFERED=%o.",_IO_UNBUFFERED);
	}else if(fp->_IO_file_flags & _IO_LINE_BUF){
		printf("line buffered,_IO_LINE_BUF=%o.",_IO_LINE_BUF);
	}else{
		printf("fully buffered!");
	}
	printf(",buffered size = %d\n",fp->_IO_buf_end-fp->_IO_buf_base);
}
