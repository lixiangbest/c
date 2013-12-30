/*************************************************************************
	> File Name: web.h
	> Description: web server header file. 
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月20日 星期五 08时13分06秒
 ************************************************************************/
#include "unp.h"

#define MAXFILES 20
#define SERV "80" /*port number or service name*/

struct file{
	char *f_name;/*filename*/
	char *f_host;/*hostname or IPv4/IPv6 address*/
	char f_fd;/*socket descriptor*/
	char f_flags;/*F_xxx below*/
}file[MAXFILES];

#define F_CONNECTING 1 /*connect() in progress*/
#define F_READING 2 /*connect() complete; now reading*/
#define F_DONE 4 /*all done*/

#define GET_CMD "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n"

/*globals*/
int nconn, nfiles, nlefttoconn, nlefttoread, maxfd;
fd_set rset, wset;

/*function prototypes*/
void home_page(const char *, const char *);
void start_connect(struct file *);
void write_get_cmd(struct file *);

