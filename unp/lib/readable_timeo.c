/*************************************************************************
	> File Name: readable_timeo.c
	> Description: select call read timeout.
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月02日 星期一 10时37分52秒
 ************************************************************************/
#include "unp.h"

int readable_timeo(int fd, int sec){
	fd_set rset;
	struct timeval tv;

	FD_ZERO(&rset);
	FD_SET(fd, &rset);

	tv.tv_sec = sec;
	tv.tv_usec = 0;

	/*> 0 if descriptor is readable*/
	return(select(fd+1, &rset, NULL, NULL, &tv));
}

int Readable_timeo(int fd, int sec){
	int n;

	if( (n = readable_timeo(fd, sec))<0)
		err_sys("readable_timeo error");
	return n;
}
