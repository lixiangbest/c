/*
 * =====================================================================================
 *
 *       Filename:  inet_ntop_ipv4.c
 *
 *    Description:  inet_ntop_ipv4 complement.
 *
 *        Version:  1.0
 *        Created:  07/13/13 16:16:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

#ifndef INET_ADDRSTRLEN
#define INET_ADDRSTRLEN 16
#endif

/*include inet_ntop*/
const char *myinet_ntop(int family, const void *addrptr, char *strptr, size_t len){
	const u_char *p = (const u_char *)addrptr;

	if(family == AF_INET){
		char temp[INET_ADDRSTRLEN];

		snprintf(temp, sizeof(temp), "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
		if(strlen(temp) >= len){
			errno = ENOSPC;
			return NULL;
		}
		strcpy(strptr, temp);
		return strptr;
	}
	errno = EAFNOSUPPORT;
	return NULL;
}

