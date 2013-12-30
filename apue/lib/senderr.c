/*
 * =====================================================================================
 *
 *       Filename:  senderr.c
 *
 *    Description:  send fd error.
 *
 *        Version:  1.0
 *        Created:  06/14/13 02:49:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

/*
 * Used when we had planned to send an fd using send_fd(),
 * but encountered an error instread. We send the error back
 * using the send_fd()/recv_fd() protocol;
 */
int send_err(int fd, int errcode, const char *msg){
	int n;

	if((n = strlen(msg)) > 0)
		if(writen(fd, msg, n) != n) /*send the error message*/
			return -1;

	if(errcode>=0)
		errcode = -1;/*must be negative*/

	if(send_fd(fd, errcode) < 0)
		return -1;

	return 0;
}
