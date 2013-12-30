/*
 * =====================================================================================
 *
 *       Filename:  servname.c
 *
 *    Description:  getservbyname and getservbyport
 *
 *        Version:  1.0
 *        Created:  11/16/13 22:21:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

void print(struct servent *sptr){
	if(sptr == NULL){
		printf("sptr is NULL\n");
		return;
	}
	printf("s_name:%s\t", sptr->s_name);
	char **pptr;
	
	for(pptr = sptr->s_aliases; *pptr != NULL; pptr++)
		printf("alias: %s\t", *pptr);
	
	printf("s_port:%d\t", ntohs(sptr->s_port));
	printf("s_proto:%s\t\n", sptr->s_proto);
}

#ifdef HAVE_SOCKADDR_DL_STRUCT
#define HN 1
#else
#define HN 0
#endif

#ifdef IPV6
#define IN 1
#else
#define IN 0
#endif

int main(void){
	struct servent *sptr;
	printf("This linux version HAVE_SOCKADDR_DL_STRUCT: %d\n", HN);
	printf("This linux version IPV6 %d\n", IN);

	sptr = getservbyname("domain", "udp");
	print(sptr);

	sptr = getservbyname("ftp", "tcp");
	print(sptr);
	
	sptr = getservbyname("ftp", NULL);
	print(sptr);
	
	sptr = getservbyname("ftp", "udp");
	print(sptr);

	sptr = getservbyname("echo", NULL);
	print(sptr);


	sptr = getservbyport(htons(53), "udp");/*DNS using UDP*/
	print(sptr);

	sptr = getservbyport(htons(21), "tcp");/*FTP using TCP*/
	print(sptr);

	sptr = getservbyport(htons(21), NULL);/*FTP using TCP*/
	print(sptr);

	sptr = getservbyport(htons(21), "udp");/*FTP using udp*/
	print(sptr);

	sptr = getservbyport(htons(7), NULL);/*echo*/
	print(sptr);

	sptr = getservbyport(htons(514), NULL);/*shell 514/tcp 514/udp*/
	print(sptr);

	sptr = getservbyport(htons(514), "tcp");/*shell 514/tcp 514/udp*/
	print(sptr);

	sptr = getservbyport(htons(514), "udp");/*shell 514/tcp 514/udp*/
	print(sptr);

	return 0;
}

