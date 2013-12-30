/*
 * =====================================================================================
 *
 *       Filename:  01_doatexit.c
 *
 *    Description:  do at exit
 *
 *        Version:  1.0
 *        Created:  05/05/13 21:34:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

static void my_exit1(void);
static void my_exit2(void);

int main(void){
	if(atexit(my_exit2)!=0){
		err_sys("can't register my_exit2");
	}
	if(atexit(my_exit1)!=0){
		err_sys("can't register my_exit1");
	}
	if(atexit(my_exit1)!=0){
		err_sys("can't register my_exit1");
	}
	printf("main is done\n");
	return(0);/*my_exit2,my_exit1 wil be run.notice the run order.*/
	/*_exit(0);my_exit2,my_exit1 will not be run.*/
}

static void my_exit1(void){
	printf("first exit handler\n");
}

static void my_exit2(void){
	printf("second exit handler\n");
}
