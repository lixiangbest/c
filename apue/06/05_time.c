/*
 * =====================================================================================
 *
 *       Filename:  04_sysinfo.c
 *
 *    Description:  sys info
 *    Usage:		$ TZ=US/Mountain ./a.out
 *    				$ TZ=Japan ./a.out
 *
 *        Version:  1.0
 *        Created:  05/01/13 16:26:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/time.h> /*gettimeofday()*/
#include<time.h> /*time()*/
#define MAXLINE 1024

int main(){
	/*notice the difference.*/
	char buf[MAXLINE];
	time_t timet;
	struct tm *p;
	char *wday[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

	struct timeval tv;
	struct timezone tz;
	
	gettimeofday(&tv, &tz);
	printf("tv_sec: %d, tv_usec: %d\n", (int)tv.tv_sec, (int)tv.tv_usec);
	printf("tz_minuteswest: %d, tz_dsttime: %d\n", tz.tz_minuteswest, tz.tz_dsttime);

	time(&timet);
	printf("time_t seconds:%d\n",(int)time((time_t*)NULL));
	printf("time_t seconds:%d\n\n",(int)timet);
	p = gmtime(&timet);/*global standard time*/
	printf("time()->gmtime():tm_sec=%d,tm_min=%d,tm_hour=%d,tm_mday=%d,tm_mon=%d,tm_year=%d,tm_wday=%s,tm_yday=%d,tm_isdst=%d\n\n",p->tm_sec,p->tm_min,p->tm_hour,p->tm_mday,(1+p->tm_mon),(1900+p->tm_year),wday[p->tm_wday],p->tm_yday,p->tm_isdst);

	p = localtime(&timet);/*local time*/
	printf("time()->localtime():tm_sec=%d,tm_min=%d,tm_hour=%d,tm_mday=%d,tm_mon=%d,tm_year=%d,tm_wday=%s,tm_yday=%d,tm_isdst=%d\n\n",p->tm_sec,p->tm_min,p->tm_hour,p->tm_mday,(1+p->tm_mon),(1900+p->tm_year),wday[p->tm_wday],p->tm_yday,p->tm_isdst);

	timet = mktime(p);
	printf("time()->localtime()->mktime():%d\n\n",(int)timet);

	printf("time()->gmtime()->asctime():%s\n", asctime(gmtime(&timet)));
	printf("time()->localtime()->asctime():%s\n", asctime(localtime(&timet)));
	
	printf("time()->ctime():%s\n", ctime(&timet));

	printf("time()->gmtime()->strftime():\n");
	printf("len:%d;", strftime(buf,MAXLINE,"%c,%Z,%G-%m-%d %H:%M:%S",gmtime(&timet)));
	printf("%s\n",buf);

	printf("\ntime()->localtime()->strftime():\n");
	printf("len:%d;", strftime(buf,MAXLINE,"%c,%Z,%G-%m-%d %H:%M:%S",localtime(&timet)));
	printf("%s\n",buf);
	return 0;
}
