/*
 * =====================================================================================
 *
 *       Filename:  inet_pton_ipv4.c
 *
 *    Description:  inet_pton_ipv4 complement.
 *
 *        Version:  1.0
 *        Created:  07/13/13 15:52:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

/*Delete following line if your system's headers already DefinE this function prototype*/
int myinet_aton(const char *, struct in_addr *);

/*include inet_pton*/
int myinet_pton(int family, const char *strptr, void *addrptr){
	if(family == AF_INET){
		struct in_addr in_val;

		if(inet_aton(strptr, &in_val)){
			memcpy(addrptr, &in_val, sizeof(struct in_addr));
			return 1;
		}
		return 0;
	}
	errno = EAFNOSUPPORT;
	return -1;
}
/*end inet_pton*/
