/*
 * =====================================================================================
 *
 *       Filename:  clrfl.c
 *
 *    Description:  clear flags.
 *
 *        Version:  1.0
 *        Created:  05/27/13 01:23:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<fcntl.h>

/*flags are the file status flags to turn off*/
void clr_fl(int fd, int flags){
	int val;

	if((val = fcntl(fd, F_GETFL, 0)) < 0){
		err_sys("fcntl F_GETFL error");
	}

	val &= ~flags;/*turn flags off*/

	if(fcntl(fd, F_SETFL, val) < 0){
		err_sys("fcntl F_SETFL error");
	}
}

