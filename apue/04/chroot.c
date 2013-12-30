/*
 * =====================================================================================
 *
 *       Filename:  chroot.c
 *
 *    Description:  chroot function usage.
 *
 *        Version:  1.0
 *        Created:  04/29/13 11:09:03
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
#include<sys/stat.h>
#include<dirent.h>
#include<errno.h>

int main(int argc, char*argv[]){
	char ptr[30];
	int size;
	struct stat st;
	struct dirent *dirp;
	DIR *dp;
	if(argc!=2){
		printf("usage is error!");
		exit(0);
	}

	if(chroot(argv[1])<0){
		printf("%s error %d:%s\n",argv[1],errno,strerror(errno));
	}else{
		printf("chroot successfully!");
	}
	/*
	if(chdir("/home")<0){
		printf("chdir failed!");
		exit(0);
	}
	*/
	
	if(getcwd(ptr, size)==NULL){
		printf("getcwd failed!");
	}else{
		printf("cwd = %s, size = %d\n", ptr, size);
	}
	
	if(chdir(ptr)<0){
		printf("chdir:%s failed!",ptr);
	}

	lstat(ptr, &st);
	if(S_ISDIR(st.st_mode)){
		if((dp = opendir(ptr))==NULL){
			printf("%s error %d:%s\n",ptr,errno,strerror(errno));
		}else{
			while((dirp = readdir(dp))!=NULL){
				printf("d_ino=%d,d_name=%s,d_type=%d\n",dirp->d_ino,dirp->d_name,dirp->d_type);
			}
		}
	}else{
		printf("%s error %d:%s\n",ptr,errno,strerror(errno));
	}
	return 0;
}

