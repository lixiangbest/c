/*
 * =====================================================================================
 *
 *       Filename:  t_ttyname.c
 *
 *    Description:  my_ttyname function usage.
 *
 *        Version:  1.0
 *        Created:  06/18/13 23:01:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<limits.h>

int main(){
	char *my_ttyname(int);
	char *name;	
	printf("_POSIX_PATH_MAX = %d\n", _POSIX_PATH_MAX);
	
	if(isatty(0)){
		name = my_ttyname(0);
		if(name == NULL) name = "undefined";
	}else{
		name = "not a tty";
	}
	printf("fd 0: %s\n", name);
	
	if(isatty(1)){
		name = ttyname(1);
		if(name == NULL) name = "undefined";
	}else{
		name = "not a tty";
	}
	printf("fd 1: %s\n", name);
	
	if(isatty(2)){
		name = my_ttyname(2);
		if(name == NULL) name = "undefined";
	}else{
		name = "not a tty";
	}
	printf("fd 2: %s\n", name);
	return 0;
}

