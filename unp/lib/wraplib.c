/*
 * =====================================================================================
 *
 *       Filename:  wraplib.c
 *
 *    Description:  Wrapper functions for our own library functions.
 *    Most are included in the source file for the function itself.
 *
 *        Version:  1.0
 *        Created:  07/06/13 22:31:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

const char *Inet_ntop(int family, const void *addrptr, char *strptr, size_t len){
	const char *ptr;

	if(strptr == NULL) /*check for old code*/
		err_quit("NULL 3rd argument to inet_ntop");
	if( (ptr = inet_ntop(family, addrptr, strptr, len)) == NULL)
		err_sys("inet_ntop error");/*sets errno*/
	return(ptr);
}

void Inet_pton(int family, const char *strptr, void *addrptr){
	int n;

	if( (n = inet_pton(family, strptr, addrptr)) < 0)
		err_sys("inet_pton error for %s", strptr);/*errno set*/
	else if(n==0)
		err_quit("inet_pton error for %s", strptr);/*errno not set*/

	/*nothing to return*/
}

