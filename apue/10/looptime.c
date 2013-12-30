/*
 * =====================================================================================
 *
 *       Filename:  looptime.c
 *
 *    Description:  loop print time
 *
 *        Version:  1.0
 *        Created:  05/20/13 00:18:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

int main(){
	int count = 0;
	while(1){
		sleep(5);
		if(count==5){
			system("date");
			count = 0;
		}else{
			count++;
		}
	}
	exit(0);
}

