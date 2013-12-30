/*
 * =====================================================================================
 *
 *       Filename:  setfl.c
 *
 *    Description:  set file flags.
 *
 *        Version:  1.0
 *        Created:  04/21/13 12:14:17
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

/*flags are file status flags to turn on*/
void set_fl(int fd, int flags){
	int val;
	if((val=fcntl(fd, F_GETFL, 0)) < 0)
		err_sys("fcntl F_GETFL error");

	val |= flags;/*turn on flags*/

	if(fcntl(fd, F_SETFL, val) < 0)
		err_sys("fcntl F_SETFL error");
}

