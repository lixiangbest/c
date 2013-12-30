/*
 * =====================================================================================
 *
 *       Filename:  04_sysinfo.c
 *
 *    Description:  sys info
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
#include<sys/utsname.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

int main(){
	struct utsname buff;
	clock_t c_start;
	c_start = clock();
	if(uname(&buff)<0){
		perror("uname");
		return 1;
	}
	printf("system name:%s\n",buff.sysname);
	sleep(3);
	printf("node name:%s\n",buff.nodename);
	printf("release:%s\n",buff.release);
	printf("version:%s\n",buff.version);
	printf("machine:%s\n",buff.machine);
	printf("run time:%f",(double)(clock()-c_start));
	return 0;
}

