/*
 * =====================================================================================
 *
 *       Filename:  sockfd_to_family.c
 *
 *    Description:  get address family fro sockfd.
 *
 *        Version:  1.0
 *        Created:  07/14/13 22:40:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
/*include sockfd_to_family*/
#include "unp.h"

int sockfd_to_family(int sockfd){
	struct sockaddr_storage ss;/*for we don't know the addr struct type.*/
	socklen_t len;

	len = sizeof(ss);
	if(getsockname(sockfd, (SA*)&ss, &len) < 0)
		return -1;
	return(ss.ss_family);
}

int Sockfd_to_family(int sockfd){
	int rc;

	if( (rc = sockfd_to_family(sockfd)) < 0)
		err_sys("sockfd_to_family error");

	return rc;
}
