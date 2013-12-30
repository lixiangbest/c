/*************************************************************************
	> File Name: lib/gf_time.c
	> Description: 
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月19日 星期四 09时35分39秒
 ************************************************************************/
#include "unp.h"
#include<time.h>

char *gf_time(void){
	struct timeval tv;
	static char str[30];
	char *ptr;

	if(gettimeofday(&tv, NULL) < 0)
		err_sys("gettimeofday error");

	ptr = ctime(&tv.tv_sec);
	strcpy(str, &ptr[11]);
	/* Fri Sep 13 00:00:00 1986\n\0*/
	/* 0123456789012345678901234 5*/
	snprintf(str + 8, sizeof(str) - 8, ".%06ld", tv.tv_usec);

	return str;
}

