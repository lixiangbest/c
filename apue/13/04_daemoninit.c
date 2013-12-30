/*
 * =====================================================================================
 *
 *       Filename:  04_daemoninit.c
 *
 *    Description:  daemon init usage.
 *
 *        Version:  1.0
 *        Created:  05/26/13 23:08:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

int main(void){
	FILE *fp;
	char *p;
	void daemonize(const char *);

	daemonize("getlog");
	p = getlogin();
	fp = fopen("/tmp/getlog.out", "w+");
	if(fp != NULL){
		if(p == NULL){
			fprintf(fp, "no login name\n");
		}else{
			fprintf(fp, "login name: %s\n", p);
		}
	}
	while(1) sleep(1);
	exit(0);
}

