/*
 * =====================================================================================
 *
 *       Filename:  pathalloc.c
 *
 *    Description:  alloc space for the file path.
 *    				P39 2-3
 *
 *        Version:  1.0
 *        Created:  04/20/13 14:40:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<errno.h>
#include<limits.h>

#ifdef PATH_MAX
static int pathmax = PATH_MAX;
#else
static int pathmax = 0;
#endif

#define SUSV3 200123L

static long posix_version = 0;

/* If PATH_MAX is indeterminate, no guarantee this is adequate */
#define PATH_MAX_GUESS 1024

/*also return allocated size, if nonull*/
char *path_alloc(int *sizep){
	char *ptr;
	int size;
	if(posix_version==0){
		posix_version = sysconf(_SC_VERSION);
	}
	printf("posix:%ld,pathmax=%d\n",posix_version,pathmax);	
	/*first time through*/
	if(pathmax==0){
		errno = 0;
		if((pathmax=pathconf("/", _PC_PATH_MAX)) < 0){
			if(errno==0){
				pathmax = PATH_MAX_GUESS;/*it's indeterminate*/
			}else{
				err_sys("pathconf error for _PC_PATH_MAX");
			}
		}else{
			pathmax++;/*add one since it's relative to root*/
		}
	}
	if(posix_version < SUSV3){
		size = pathmax + 1;
	}else{
		size = pathmax;
	}

	printf("pathmax=%d,size=%d,posix_version=%ld\n",pathmax,size,posix_version);
	if((ptr=malloc(size))==NULL){
		err_sys("malloc error for pathname");
	}

	if(sizep!=NULL){
		*sizep = size;
	}
	return ptr;
}
