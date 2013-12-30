/*
 * =====================================================================================
 *
 *       Filename:  netfunc.c
 *
 *    Description:  net exchange functions.
 *
 *        Version:  1.0
 *        Created:  07/13/13 12:19:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

int main(void){
	int b1,b2;
	long int m1,m2;
	uint16_t port;/*ip port*/
	uint32_t host;/*ip host*/

	port = htons(8080);/*host to network short*/
	printf("ip port: 0x%x, ip net port: 0x%x\n", 8080, port);
	printf("ip port: 0x%x\n\n", ntohs(port));

	host = htonl(0xffffff10);/*host to network short*/
	printf("ip host: 0x%x, ip net host: 0x%x\n", 0xffffff10, host);
	printf("ip host: 0x%x\n\n", ntohl(host));
	
	bzero(&b1,sizeof(b1));
	printf("bzero(int):0x%x\n", b1);
	b1 = 10;
	bcopy(&b1, &b2, sizeof(b2));
	printf("bcopy 0x%x, 0x%x, bcmp: 0x%x\n\n", b1, b2, bcmp(&b1, &b2, sizeof(b2)));
	
	memset(&m1, 0, sizeof(m1));
	printf("bzero(long int):0x%lx\n", m1);
	m1 = 20;
	memcpy(&m2, &m1, sizeof(m2));
	printf("bcopy 0x%lx, 0x%lx, bcmp: 0x%x\n\n", m1, m2, memcmp(&m1, &m2, sizeof(m2)));

	char straddr[] = "255.255.255.16";
	struct in_addr addr;
	printf("inet_aton:%d\n", inet_aton(straddr, &addr));
	printf("straddr:%s, in_addr:0x%x\n", straddr, addr);
	printf("inet_addr:0x%x\n", inet_addr(straddr));/*INADDR_NONE=0xffffffff*/
	printf("inet_ntoa:%s\n\n", inet_ntoa(addr));

	/*if(myinet_pton(AF_UNIX, NULL, NULL) < 0)*/
	if(inet_pton(AF_UNIX, NULL, NULL) < 0)
		perror("inet_pton");
	char pstr[] = "255.255.255.17";
	char nstr[16];
	struct in_addr paddr;
	printf("inet_pton:%d\n", inet_pton(AF_INET, pstr, &paddr));
	printf("presentation str:%s, addr pointer:0x%x\n", pstr, paddr);
	if(inet_ntop(AF_INET, &paddr, nstr, 5) == NULL)
		perror("inet_ntop");
	printf("inet_ntop:%s\n", inet_ntop(AF_INET, &paddr, nstr, sizeof(nstr)));
	printf("presentation:%s\n\n", nstr);

	char mystr[] = "255.255.255.20";
	char mstr[INET_ADDRSTRLEN];
	struct in_addr myaddr;
	myinet_pton(AF_INET, mystr, &myaddr);
	printf("presentation str:%s, addr pointer:0x%x\n", mystr, myaddr);
	myinet_ntop(AF_INET, &myaddr, mstr, INET_ADDRSTRLEN);
	printf("presentation:%s\n\n", mstr);

	u_char *pu = (u_char *)&myaddr;
	printf("sizeof u_char %d, %d.%d.%d.%d\n", sizeof(u_char), pu[0], pu[1], pu[2], pu[3]);

	int int_addr = 0xffffff11;
	unsigned char *pm = (unsigned char *)&int_addr;
	printf("sizeof char %d, %d.%d.%d.%d\n", sizeof(char), pm[3], pm[2], pm[1], pm[0]);

	return 0;
}

