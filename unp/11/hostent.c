/*
 * =====================================================================================
 *
 *       Filename:  hostent.c
 *
 *    Description:  host environment
 *
 *        Version:  1.0
 *        Created:  11/14/13 22:57:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

int main(int argc, char **argv){
	char *ptr, **pptr;
	char str[INET_ADDRSTRLEN];
	struct hostent *hptr;

	while(--argc > 0){
		ptr = *++argv;
		if( (hptr = gethostbyname(ptr)) == NULL){
			err_msg("gethostbyname error for host: %s: %s", ptr, hstrerror(h_errno));
			continue;
		}
		/*struct hostent.h_name*/
		printf("official hostname: %s\n", hptr->h_name);
		
		/*struct hostent.h_aliases*/
		for(pptr = hptr->h_aliases; *pptr != NULL; pptr++)
			printf("\talias: %s\n", *pptr);

		/*struct hostent.h_addrtype*/
		switch(hptr->h_addrtype){
			case AF_INET:
				pptr = hptr->h_addr_list;
				for(; *pptr != NULL; pptr++)
					printf("\taddress: %s\n", Inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
				break;
			default:
				err_ret("unkown address type");
				break;
		}
	}
	exit(0);
}

