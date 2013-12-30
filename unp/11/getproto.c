/*
 * =====================================================================================
 *
 *       Filename:  getproto.c
 *
 *    Description:  get protocol.
 *
 *        Version:  1.0
 *        Created:  11/23/13 22:54:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

int main(){
	int number;
	struct protoent *protocol;
	for(number=0; number<20; number++){
		protocol = getprotobynumber(number);
		if(protocol == (struct protoent *)NULL){
			printf("protocol NULL\n");
			continue;
		}
		printf("%2d: %-10s: %-10s\n", protocol->p_proto, protocol->p_name, protocol->p_aliases[0]);
	}
	return 0;
}

