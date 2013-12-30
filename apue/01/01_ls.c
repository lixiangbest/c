/*
 * =====================================================================================
 *
 *       Filename:  01_ls.c
 *
 *    Description:  LS command can list the file in the given dir.
 *
 *        Version:  1.0
 *        Created:  04/16/13 02:49:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */

#include "apue.h"
#include <dirent.h>

int main(int argc, char *argv[]){
	DIR *dp;/* typedef struct __dirstream DIR  */
	struct dirent *dirp;
	if(argc!=2){
		err_quit("usage: ls directory_name!");
	}
	
	if((dp=opendir(argv[1])) == NULL){
		err_sys("can't open %s", argv[1]);
	}
	/*traverse the directory*/
	while((dirp=readdir(dp)) != NULL){
		/* struct dirent{
		 *   long d_ino;//inode number
		 *   off_t d_off;//offset to this dirent
		 *   unsigned short d_reclen;//length of this d_name
		 *   unsigned char d_type;//the type of d_name
		 *   char d_name[NAME_MAX+1];//file name,max 255 char
		 * } 
		*/
		printf("%s,%ld,%d,%d\n",dirp->d_name,dirp->d_ino,dirp->d_reclen,NAME_MAX);
	}
	/*you must close the dir after you have handled it.*/
	closedir(dp);
	exit(0);
}
