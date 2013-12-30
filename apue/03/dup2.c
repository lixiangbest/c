/*
 * =====================================================================================
 *
 *       Filename:  dup2.c
 *
 *    Description:  create a function like dup2.
 *
 *        Version:  1.0
 *        Created:  04/22/13 21:41:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h> /*fprintf()*/
#include<stdlib.h> /*exit() perror()*/
#include<string.h> /*strlen()*/
#include<unistd.h> /*dup() write()*/
#include<errno.h> /*errno*/

/*modup2: like dup2()*/
int modup2(int filedesc, int filedesc2){
	int fd, tmpfd, fds[filedesc2];
	int errsv = 0;

	if(filedesc < 0
#ifdef OPEN_MAX
		|| filedesc >= OPEN_MAX
#endif
	){
		fprintf(stderr, "filedesc:invalid file descriptor %d\n", filedesc);
		return -1;
	}
	/*test the OPEN file MAX.*/
	if(filedesc2 < 0
	#ifdef OPEN_MAX
		|| filedesc2 >= OPEN_MAX
	#endif
	){
		fprintf(stderr, "filedec2:invalid file descriptor %d\n", filedesc2);
		return -1;
	}

	/*filedes equal to filedes2*/
	if(filedesc == filedesc2){
		return filedesc2;
	}

	/*if filedesc2 is exist,tmpfd>=0; else tmpfd <0*/
	if((tmpfd = dup(filedesc2)) != -1){
		//close the exist filedesc2
		if(close(filedesc2) == -1)
			perror("close");
		if(close(tmpfd) == -1)
			perror("close");
	}
	printf("\ntmpfd:%d\n",tmpfd);

	int i = 0;
	//start copy.fd will increase until equal to filedesc2.
	while((fd=dup(filedesc)) != filedesc2){
		if(fd == -1){
			errsv = fd;
			break;
		}
		fds[i++] = fd;
	}

	int j;
	for(j=0;j<i;j++){
		if(close(fds[j])==-1){
			perror("close");
		}
	}
	/*none error.*/
	if(errsv!=0){
		errno = errsv;
		return -1;
	}
	return filedesc2;
}

/*test driver*/
int main(void){
	int fd, n;
	char buf[] = "just do it.\n";

	n = strlen(buf);
	
	printf("\tmodup2(STDOUT_FILENO, 5):\n");
	fd = modup2(STDOUT_FILENO, 5);
	if(write(fd, buf, n)!=n)
		perror("write");

	printf("\tmodup2(-1, 6):\n");
	fd = modup2(-1, 6);
	if(write(fd, buf, n)!=n)
		perror("write");

	printf("\tmodup2(1, -1):\n");
	fd = modup2(1, -1);
	if(write(fd, buf, n)!=n)
		perror("write");

	printf("\tmodup2(1, 2):\n");
	fd = modup2(1, 2);
	if(write(fd, buf, n)!=n)
		perror("write");

	exit(0);
}
