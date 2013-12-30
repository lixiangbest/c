/*
 * =====================================================================================
 *
 *       Filename:  getenv1.c
 *
 *    Description:  getenv
 *
 *        Version:  1.0
 *        Created:  05/24/13 23:14:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<limits.h>
#include<string.h>

#ifndef ARG_MAX
	#define ARG_MAX 10000
#endif

static char envbuf[ARG_MAX];

extern char **environ;

char *getenv(const char *name){
	int i, len;

	len = strlen(name);
	for(i=0;environ[i] != NULL;i++){
		if((strncmp(name, environ[i], len) == 0) && (environ[i][len] == '=')){
			strcpy(envbuf, &environ[i][len+1]);
			return(envbuf);
		}
	}
	return(NULL);
}

