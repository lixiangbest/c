/*
 * =====================================================================================
 *
 *       Filename:  07_ftw.c
 *
 *    Description:  ftw
 *
 *        Version:  1.0
 *        Created:  04/24/13 07:14:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<dirent.h>
#include<limits.h>
#include<time.h>

/*function type that is called for each filename*/
typedef int Myfunc(const char *, const struct stat *, int);

static Myfunc myfunc;
static int myftw(char *, Myfunc *);
static int dopath(Myfunc *);

/*cout the amount of each file type.*/
static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char *argv[]){
	int ret;
	clock_t c_start,c_end;
	c_start = clock();
	if(argc!=2){
		err_quit("usage: ftw <starting-pathname>");
	}
	ret = myftw(argv[1], myfunc);/*does it all. myfunc is our defined func.*/
	/*compute the amount.*/
	ntot = nreg + ndir + nblk + nchr + nfifo +nslink + nsock;
	if(ntot==0)
		ntot = 1;/*avoid divide by 0; print 0 for all counts*/
	printf("regular files = %7ld, %5.2f %%\n", nreg, nreg*100.0/ntot);
	printf("directories = %7ld, %5.2f %%\n", ndir, ndir*100.0/ntot);
	printf("block special = %7ld, %5.2f %%\n", nchr, nchr*100.0/ntot);
	printf("char special = %7ld, %5.2f %%\n", nfifo, nfifo*100.0/ntot);
	printf("FIFOs = %7ld, %5.2f %%\n", nfifo, nfifo*100.0/ntot);
	printf("symbolic links = %7ld, %5.2f %%\n", nslink, nslink*100.0/ntot);
	printf("sockets = %7ld, %5.2f %%\n", nsock, nsock*100.0/ntot);
	c_end = clock();
	printf("PER_SEC=%f,elapsed:%f seconds\n",(double)CLOCKS_PER_SEC,(c_end-c_start)/(double)CLOCKS_PER_SEC);
	exit(ret);
}

/*
 * Descend through the hierarchy, starting at "pathname".
 * The caller's func() is called for every file.
 */
#define FTW_F 1 /*file other than directory*/
#define FTW_D 2 /*directory*/
#define FTW_DNR 3 /*directory that can't be read*/
#define FTW_NS 4 /*file that we can't stat*/

static char *fullpath; /*contains full pathname for every file*/

/*we return whatever func() returns*/
static int myftw(char *pathname, Myfunc *func){
	int len;
	/*our defined function*/
	fullpath = path_alloc(&len);/*malloc's for PATH_MAX+1 bytes*/
	strncpy(fullpath, pathname, len);/*protect against*/
	fullpath[len-1] = 0;/*buffer overrun*/
	return(dopath(func));
}

/* Descend through the hierarchy, starting at "fullpath".
 * If "fullpath" is anything other than a directory, we lstat() it,
 * call func(), and return. For a directory, we call ourself
 * recursively for each name in the directory.
 */
static int dopath(Myfunc* func){/*we return whatever func() returns*/
	struct stat statbuf;
	struct dirent *dirp;
	DIR *dp;
	int ret;
	char *ptr;
	/*stat error*/
	if(lstat(fullpath, &statbuf) < 0){
		return(func(fullpath, &statbuf, FTW_NS));
	}
	/*not a directory*/
	if(S_ISDIR(statbuf.st_mode)==0){
		return(func(fullpath, &statbuf, FTW_F));
	}
	
	/*
	 * it's a directory. First call func() for the directory.
	 * then process each filename in the directory.
	 */
	if((ret = func(fullpath, &statbuf, FTW_D)) != 0){
		return(ret);
	}

	ptr = fullpath + strlen(fullpath);/*point to end of fullpath*/
	*ptr++ = '/';/*use the absolute path*/
	*ptr = 0;
	
	/*can't read directory*/
	if((dp = opendir(fullpath)) == NULL){
		return(func(fullpath, &statbuf, FTW_DNR));
	}

	/*start processing each filename in the directory.*/
	while((dirp = readdir(dp)) != NULL){
		if(strcmp(dirp->d_name, ".")==0 || strcmp(dirp->d_name, "..")==0)
			continue;/*ignore dot and dot-dot*/

		strcpy(ptr, dirp->d_name);/*append name after slash*/
		/*recursive*/
		if((ret = dopath(func)) != 0)
			break;/*time to leave*/
	}
	ptr[-1] = 0;/*erase everything from slash onwards*/

	if(closedir(dp) < 0)
		err_ret("can't close directory %s", fullpath);

	return(ret);
}

/*main func*/
static int myfunc(const char*pathname, const struct stat *statptr, int type){
	switch(type){
		/*file*/
		case FTW_F:
			switch(statptr->st_mode & S_IFMT){
				case S_IFREG: nreg++;break;
				case S_IFBLK: nblk++;break;
				case S_IFCHR: nchr++;break;
				case S_IFIFO: nfifo++;break;
				case S_IFLNK: nslink++;break;
				case S_IFSOCK: nsock++;break;
				case S_IFDIR:
					err_dump("for S_IFDIR for %s", pathname);
				/*directories should have type = FTW_D*/
			}
			break;
		/*directory*/
		case FTW_D:
			ndir++;
			break;
		/*don't read*/
		case FTW_DNR:
			err_ret("can't read directory %s", pathname);
			break;
		/*can't not stat*/
		case FTW_NS:
			err_ret("stat error for %s", pathname);
			break;
		default:
			err_dump("unknown type %d for pathname %s", type, pathname);
	}
	return(0);
}

