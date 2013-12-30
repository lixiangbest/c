/*
 * =====================================================================================
 *
 *       Filename:  02_vfork2.c
 *
 *    Description:  vfork
 *
 *        Version:  1.0
 *        Created:  05/11/13 23:35:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

static void f1(void), f2(void);

int main(void){
	f1();
	f2();
	_exit(0);
}

static void f1(void){
	pid_t pid;
	if((pid=vfork()) < 0)
		err_sys("vfork error");
	/*child and parent both return*/
}

static void f2(void){
	char buf[1000];/*automatic variables*/
	int i;
	for(i=0;i<sizeof(buf);i++){
		buf[i] = 0;
	}
}

