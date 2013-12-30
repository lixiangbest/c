/*
 * =====================================================================================
 *
 *       Filename:  clconn.c
 *
 *    Description:  retry connect.
 *
 *        Version:  1.0
 *        Created:  06/11/13 00:14:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<sys/socket.h>

#define MAXSLEEP 128 /*2 7*/

int connect_retry(int sockfd, const struct sockaddr *addr, socklen_t alen){
	int nsec;

	/*Try to connect with exponential backoff*/
	for(nsec = 1; nsec <= MAXSLEEP; nsec <<= 1){
		if(connect(sockfd, addr, alen) == 0){
			/*connection accepted.*/
			return 0;
		}

		/*
		 * Delay before trying again.
		 */
		if(nsec <= MAXSLEEP/2)
			sleep(nsec);
	}
	return -1;
}
