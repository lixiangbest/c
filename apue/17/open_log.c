/*
 * =====================================================================================
 *
 *       Filename:  open_log.c
 *
 *    Description:  syslog function usage.
 *    				./open_log
 *					./open_log -a -b
 *					./open_log -ab
 *					./open_log -c foo
 *					./open_log -cfoo
 *					./open_log arg1
 *					./open_log -a arg1
 *					./open_log -c foo arg1
 *					./open_log -a -- -b
 *					./open_log -a -
 *
 *        Version:  1.0
 *        Created:  06/16/13 14:53:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<syslog.h>
#include<errno.h>
#include<ctype.h>

int main(int argc, char *argv[]){
	int write;
	char buf[MAXLINE] = "Nike";

	/*snprintf function usage.*/
	write = snprintf(buf+strlen(buf), MAXLINE-strlen(buf),"%s,%d", "and Anta", 2);
	printf("buf:%s; want write:%d; buf len:%d\n", buf, write, strlen(buf));

	/*use openlog function*/
	/*
	openlog("testsyslog", LOG_CONS | LOG_PID, 0);
	syslog(LOG_USER | LOG_INFO, "syslog test message generated in program %s\n", argv[0]);
	closelog();
	*/
	/*
	openlog("here", LOG_CONS | LOG_PID, LOG_USER);
	syslog(LOG_LOCAL2 | LOG_INFO, "syslog test message generated in program %s\n", argv[0]);
	closelog();
	*/
	/*setlogmask(LOG_UPTO (LOG_NOTICE));*//*accept LOG_NOTICE, and to reject all other messages*/
	/*
	openlog("exampleprog", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
	syslog(LOG_NOTICE, "Program started by User %d", getuid());
	syslog(LOG_INFO, "A tree falls in a forest");
	closelog();
	*/

	/*use the getopt function.*/
	int aflag = 0;
	int bflag = 0;
	char *cvalue = NULL;
	int index;
	int c;

	if(!isprint(1))	printf("is not print!\n");

	opterr = 1;/*output getopt error msg.*/
	while((c = getopt(argc, argv, "abc:")) != -1)
			switch(c){
				case 'a':
					aflag = 1;break;
				case 'b':
					bflag = 1;break;
				case 'c':
					cvalue = optarg;break;
				case '?':
					if(optopt == 'c')
						fprintf(stderr, "Option -%c requires an argument.\n", optopt);
					else if(isprint(optopt))
						fprintf(stderr, "Unknown option '-%c'.\n", optopt);
					else
						fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
					return 1;
				default:
					abort();
			}
	printf("argc = %d, optind = %d, aflag = %d, bflag = %d, cvalue = %s\n", argc, optind, aflag, bflag, cvalue);
	for(index = optind; index < argc; index++)
		printf("Non-option argument %d:%s\n", index, argv[index]);

	errno = 1;
	err_quit("you know the function return:%s", "Watching");
	err_sys("you know the function return:%s", "Watching");
	err_ret("you know the function return:%s", "Watching");

	return 0;
}
