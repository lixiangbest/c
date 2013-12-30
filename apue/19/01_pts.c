/*
 * =====================================================================================
 *
 *       Filename:  01_pts.c
 *
 *    Description:  get the ssh terminate pts.
 *
 *        Version:  1.0
 *        Created:  06/24/13 02:23:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<fcntl.h>
#include<sys/ioctl.h>
#include<stropts.h>

#ifdef TIOCGWINSZ
int is_tioc = 1;
#else
int is_tioc = 0;
#endif

#ifdef _HAS_OPENPT
int is_openpt = 1;
#else
int is_openpt = 0;
#endif

#ifdef _HAS_PTSNAME
int is_ptsname = 1;
#else
int is_ptsname = 0;
#endif

#ifdef _HAS_GRANTPT
int is_grantpt = 1;
#else
int is_grantpt = 0;
#endif

#ifdef _HAS_UNLOCKPT
int is_unlockpt = 1;
#else
int is_unlockpt = 0;
#endif


int main(){
	printf("fd 0: %s\n", ttyname(0));
	printf("fd 1: %s\n", ttyname(1));
	printf("fd 2: %s\n", ttyname(2));

	printf("TIOCGWINSZ = %d\n", is_tioc);

	printf("/dev/ptmx = %d\n", open("/dev/ptmx", O_RDONLY));

	printf("_HAS_OPENPT = %d\n", is_openpt);
	printf("_HAS_PTSNAME = %d\n", is_ptsname);
	printf("_HAS_GRANTPT = %d\n", is_grantpt);
	printf("_HAS_UNLOCKPT = %d\n", is_unlockpt);

	return 0;
}
