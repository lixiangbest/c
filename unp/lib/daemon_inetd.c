/*************************************************************************
	> File Name: daemon_inetd.c
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月02日 星期一 03时08分47秒
 ************************************************************************/
#include "unp.h"
#include<syslog.h>

extern int daemon_proc;/*defined in error.c*/

void daemon_inetd(const char *pname, int facility){
	daemon_proc = 1;/*for our err_XXX() functions*/
	openlog(pname, LOG_PID, facility);
}
