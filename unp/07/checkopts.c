/*
 * =====================================================================================
 *
 *       Filename:  checkopts.c
 *
 *    Description:  check socket options.
 *
 *        Version:  1.0
 *        Created:  08/04/13 15:02:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
/*include checkopts1*/
/*INDENT-OFF*/
#include "unp.h"
#include<netinet/tcp.h> /*for TCP_xxx defines*/

/*our define*/
union myval{
	int i_val;
	//long l_val;
	struct linger linger_val;
	struct timeval timeval_val;
}uval;

static char *sock_str_flag(union myval *, int);
static char *sock_str_int(union myval *, int);
static char *sock_str_linger(union myval *, int);
static char *sock_str_timeval(union myval *, int);

struct mysock_opts{
	const char *opt_str;
	int opt_level;
	int opt_name;
	char *(*opt_val_str)(union myval *, int);
}arr_sock_opts[] = {
	{"SO_BROADCAST", SOL_SOCKET, SO_BROADCAST, sock_str_flag},
	{"SO_DEBUG", 	 SOL_SOCKET, SO_DEBUG, 	   sock_str_flag},
	{"SO_DONTROUTE", SOL_SOCKET, SO_DONTROUTE, sock_str_flag},
	{"SO_ERROR", 	 SOL_SOCKET, SO_ERROR, 	   sock_str_int},
	{"SO_KEEPALIVE", SOL_SOCKET, SO_KEEPALIVE, sock_str_flag},
	{"SO_LINGER", 	 SOL_SOCKET, SO_LINGER,    sock_str_linger},
	{"SO_OOBINLINE", SOL_SOCKET, SO_OOBINLINE, sock_str_flag},
	{"SO_RCVBUF", 	 SOL_SOCKET, SO_RCVBUF,    sock_str_int},
	{"SO_SNDBUF", 	 SOL_SOCKET, SO_SNDBUF,   sock_str_int},
	{"SO_RCVLOWAT",  SOL_SOCKET, SO_RCVLOWAT,  sock_str_int},
	{"SO_SNDLOWAT",	 SOL_SOCKET, SO_SNDLOWAT,  sock_str_int},
	{"SO_RCVTIMEO",  SOL_SOCKET, SO_RCVTIMEO,  sock_str_timeval},
	{"SO_SNDTIMEO",  SOL_SOCKET, SO_SNDTIMEO,  sock_str_timeval},
	{"SO_REUSEADDR", SOL_SOCKET, SO_REUSEADDR, sock_str_flag},
#ifdef SO_REUSEPORT
	{"SO_REUSEPORT", SOL_SOCKET, SO_REUSEPORT, sock_str_flag},
#else
	{"SO_REUSEPORT", 0,			 0,			   NULL},
#endif

	{"SO_TYPE", 	 SOL_SOCKET, SO_TYPE, 	   sock_str_int},

#ifdef SO_USELOOPBACK
	{"SO_USELOOPBACK", SOL_SOCKET, SO_USELOOPBACK, sock_str_flag},
#else
	{"SO_USELOOPBACK", 0,			 0,			   NULL},
#endif

	{"IP_TOS", 		 IPPROTO_IP, IP_TOS, sock_str_int},
	{"IP_TTL", 		 IPPROTO_IP, IP_TTL, sock_str_int},

#ifdef IPV6_DONTFRAG
	{"IPV6_DONTFRAG", IPPROTO_IPV6, IPV6_DONTFRAG, sock_str_flag},
#else
	{"IPV6_DONTFRAG", 0,			 0,			   NULL},
#endif

	{"IPV6_UNICAST_HOPS", IPPROTO_IPV6, IPV6_UNICAST_HOPS, sock_str_int},
	{"IPV6_V6ONLY",   IPPROTO_IPV6, IPV6_V6ONLY, sock_str_flag},

	{"TCP_MAXSEG",	  IPPROTO_TCP,  TCP_MAXSEG,   sock_str_int},
	{"TCP_NODELAY",	  IPPROTO_TCP,  TCP_NODELAY,  sock_str_flag},

#ifdef SCTP_AUTOCLOSE
	{"SCTP_AUTOCLOSE", IPPROTO_SCTP, SCTP_AUTOCLOSE, sock_str_int},
#else
	{"SCTP_AUTOCLOSE", 0,			 0,			   NULL},
#endif

#ifdef SCTP_MAXBURST
	{"SCTP_MAXBURST", IPPROTO_SCTP, SCTP_MAXBURST,  sock_str_int},
#else
	{"SCTP_MAXBURST", 0,			 0,			   NULL},
#endif

#ifdef SCTP_NODELAY
	{"SCTP_MAXBURST",  IPPROTO_SCTP, SCTP_MAXSEG,    sock_str_int},
#else
	{"SCTP_MAXBURST", 0,			 0,			   NULL},
#endif
	{NULL, 			  0,			 0,			 	 NULL}
};

int main(int argc, char **argv){
	int fd;
	socklen_t len;
	struct mysock_opts *ptr;

	printf("sock_stream:%d\n", SOCK_STREAM);
	printf("sizeof int:%d,long:%d,linger:%d,timeval:%d\n", sizeof(int), sizeof(long), sizeof(struct linger), sizeof(struct timeval));
	printf("sizeof union myval:%d\n", sizeof(uval));
	for(ptr = arr_sock_opts; ptr->opt_str != NULL; ptr++){
		printf("%s: ", ptr->opt_str);
		/*handle function*/
		if(ptr->opt_val_str == NULL){
			printf("(undefined)\n");
		}else{
			switch(ptr->opt_level){
				case SOL_SOCKET:
				case IPPROTO_IP:
				case IPPROTO_TCP:
					fd = Socket(AF_INET, SOCK_STREAM, 0);
					break;
#ifdef IPV6
				case IPPROTO_IPV6:
					fd = Socket(AF_INET6, SOCK_STREAM, 0);
					break;
#endif
#ifdef IPPROTO_SCTP
				case IPPROTO_SCTP:
					fd = Socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
					break;
#endif
				default:
					err_quit("Can't create fd for level %d\n", ptr->opt_level);
			}

			len = sizeof(uval);/*union myval*/
			if(getsockopt(fd, ptr->opt_level, ptr->opt_name, &uval, &len) == -1){
				err_ret("getsockopt error");
			}else{
				printf("default = %s\n", (*ptr->opt_val_str)(&uval, len));
			}
			close(fd);
		}
	}
	exit(0);
}
/*end checkopts2*/

/*include checkopts3*/
static char strres[128];

static char *sock_str_flag(union myval *ptr, int len){
	/*indent-off*/
	if(len != sizeof(int))
		snprintf(strres, sizeof(strres), "size (%d) not sizeof(int)", len);
	else
		snprintf(strres, sizeof(strres), "%s", (ptr->i_val == 0)?"off":"on");
	return(strres);
	/*indent-on*/
}
/*end checkopts3*/

static char *sock_str_int(union myval *ptr, int len){
	if(len != sizeof(int))
		snprintf(strres, sizeof(strres), "size (%d) not sizeof(int)", len);
	else
		snprintf(strres, sizeof(strres), "%d", ptr->i_val);
	return(strres);
}

static char *sock_str_linger(union myval *ptr, int len){
	struct linger *lptr = &ptr->linger_val;

	if(len != sizeof(struct linger))
		snprintf(strres, sizeof(strres), "size (%d) not sizeof(int)", len);
	else
		snprintf(strres, sizeof(strres), "l_onoff = %d, l_linger = %d", lptr->l_onoff, lptr->l_linger);
	return(strres);
}

static char *sock_str_timeval(union myval *ptr, int len){
	struct timeval *tvptr = &ptr->timeval_val;

	if(len != sizeof(struct timeval))
		snprintf(strres, sizeof(strres), "size (%d) not sizeof(int)", len);
	else
		snprintf(strres, sizeof(strres), "%d sec, %d usec", (int)tvptr->tv_sec, (int)tvptr->tv_usec);
	return(strres);
}
