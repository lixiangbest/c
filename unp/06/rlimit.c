/*
 * =====================================================================================
 *
 *       Filename:  rlimit.c
 *
 *    Description:  rlimit
 *
 *        Version:  1.0
 *        Created:  07/25/13 21:43:11
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
	struct rlimit rlp;
	printf("FD_SETSIZE: 0x%x\n", FD_SETSIZE);
	getrlimit(RLIMIT_NOFILE, &rlp);
	printf("NOFILE rlp: 0x%x, 0x%x\n", rlp.rlim_cur, rlp.rlim_max);
	getrlimit(RLIMIT_CPU, &rlp);
	printf("CPU rlp: 0x%x, 0x%x\n", rlp.rlim_cur, rlp.rlim_max);
	getrlimit(RLIMIT_LOCKS, &rlp);
	printf("LOCKS rlp: 0x%x, 0x%x\n", rlp.rlim_cur, rlp.rlim_max);
	
	return 0;
}
