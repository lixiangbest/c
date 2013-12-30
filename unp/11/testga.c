/*
 * =====================================================================================
 *
 *       Filename:  testga.c
 *
 *    Description:  test get address info command line.
 *
 *        Version:  1.0
 *        Created:  11/22/13 00:17:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "unp.h"

/*
 * Test program for getaddrinfo() and getnameinfo();
 */

/*function prototypes for internal function*/
static void do_err_test(void);
static void do_func_call(const char *, const char *, int, int, int, int, int);
static int do_one_test(char *, char *, struct addrinfo *, int);
static const char *str_fam(int);
static const char *str_sock(int);
static void usage(const char *);

/*globals*/
int vflag;

int main(int argc, char **argv){
	int doerrtest = 0;
	int loopcount = 1;
	int c, i;
	char *host = NULL;
	char hostbuf[NI_MAXHOST];
	char *serv = NULL;
	char servbuf[NI_MAXSERV];
	struct protoent *proto;
	struct addrinfo hints;/*set by command-line options*/
	
	printf("NI_MAXHOST:%d, NI_MAXSERV:%d\n", NI_MAXHOST, NI_MAXSERV);
	/*show the usage of this command.*/
	if(argc < 2){
		usage("");
	}
	memset(&hints, 0, sizeof(struct addrinfo));
	
	opterr = 0;/*don't want getopt() writing to stderr*/
	while( (c = getopt(argc, argv, "cef:h:l:pr:s:t:v")) != -1){
		switch(c){
			case 'c':
				hints.ai_flags |= AI_CANONNAME;
				break;
			case 'e':
				doerrtest = 1;
				break;
			case 'f': /*address family*/
#ifdef IPv4
				if(strcmp(optarg, "inet")==0){
					hints.ai_family = AF_INET;
					break;
				}
#endif
#ifdef IPv6
				if(strcmp(optarg, "inet6")==0){
					hints.ai_family = AF_INET6;
					break;
				}
#endif
#ifdef UNIXdomain				
				if(strcmp(optarg, "unix")==0){
					hints.ai_family = AF_LOCAL;
					break;
				}
#endif
				usage("invalid -f option");
			case 'h':
				strncpy(hostbuf, optarg, NI_MAXHOST-1);
				host = hostbuf;
				break;
			case 'l':
				loopcount = atoi(optarg);
				break;
			case 'p':
				hints.ai_flags |= AI_PASSIVE;
				break;
			case 'r': /*protocol*/
				if((proto = getprotobyname(optarg)) == NULL){
					hints.ai_protocol = atoi(optarg);
				}else{
					hints.ai_protocol = proto->p_proto;
				}
				break;
			case 's':
				strncpy(servbuf, optarg, NI_MAXSERV-1);
				serv = servbuf;
				break;
			case 't':
				if(strcmp(optarg, "stream") == 0){
					hints.ai_socktype = SOCK_STREAM;
					break;
				}
				if(strcmp(optarg, "dgram") == 0){
					hints.ai_socktype = SOCK_DGRAM;
					break;
				}
				if(strcmp(optarg, "raw") == 0){
					hints.ai_socktype = SOCK_RAW;
					break;
				}
#ifdef SOCK_RDM
				if(strcmp(optarg, "rdm") == 0){
					hints.ai_socktype = SOCK_RDM;
					break;
				}
#endif
#ifdef SOCK_SEQPACKET
				if(strcmp(optarg, "seqpacket") == 0){
					hints.ai_socktype = SOCK_SEQPACKET;
					break;
				}
#endif
				usage("invalid -t option");
			case 'v':
				vflag = 1;
				break;
			case '?':
				usage("unrecognized option");
		}
	}
	if(optind < argc){
		usage("extra args");
	}
	if(doerrtest){
		do_err_test();
	}

	for(i = 1; i<= loopcount; i++){
		if(do_one_test(host, serv, &hints, i) > 0)
			exit(1);
		if(i%1000==0){
			printf(" %d", i);
			fflush(stdout);
		}
	}
	return 0;
}

static int do_one_test(char *host, char *serv, struct addrinfo *hints, int iteration){
	int rc, fd, verbose;
	struct addrinfo *res, *rescopy;
	char rhost[NI_MAXHOST], rserv[NI_MAXSERV];

	verbose = vflag && (iteration==1);/*only first time*/
	if(host != NULL && verbose)
		printf("host = %s\n", host);
	if(serv != NULL && verbose)
		printf("serv = %s\n", serv);
	rc = getaddrinfo(host, serv, hints, &res);
	if(rc != 0){
		printf("getaddrinfo return code = %d (%s)\n", rc, gai_strerror(rc));
		return(1);
	}
	
	rescopy = res;
	do{
		if(iteration == 1){/*always print results first time*/
			printf("\nsocket(%s, %s, %d)", str_fam(res->ai_family), str_sock(res->ai_socktype), res->ai_protocol);
			/*canonname should be set only in first addrinfo()*/
			if(hints->ai_flags & AI_CANONNAME){
				if(res->ai_canonname)
					printf(", ai_canonname = %s", res->ai_canonname);
			}
			printf("\n");
			
			printf("\taddress: %s\n", Sock_ntop(res->ai_addr, res->ai_addrlen));
		}
		/*Call socket() to make sure return values are valid*/
		fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if(fd < 0)
			printf("call to socket() failed!\n");
		else
			close(fd);

		/*call getnameinfo() to check the reverse mapping*/
		rc = getnameinfo(res->ai_addr, res->ai_addrlen, rhost, NI_MAXHOST, rserv, NI_MAXSERV, (res->ai_socktype == SOCK_DGRAM)?NI_DGRAM:0);
		if(rc == 0){
			if(verbose)
				printf("\tgetnameinfo: host = %s, serv = %s\n", rhost, rserv);
		}else
			printf("getnameinfo returned %d (%s)\n", rc, gai_strerror(rc));
	}while( (res = res->ai_next) != NULL);
	freeaddrinfo(rescopy);
	return(0);
}

/* Check that the right error codes are returned for invalid input.
 * Test all the errors that are easy to test for.
 */
static void do_err_test(void){
	/*passive open with no hostname and no address family*/
	do_func_call(NULL, "ftp", AI_PASSIVE, 0, 0, 0, 0);
	/*kind of hard to automatically test EAI_AGAIN ???*/
	/*invalid flags*/
	do_func_call("localhost", NULL, 999999, 0, 0, 0, EAI_BADFLAGS);
	/*how to test EAI_FAIL ???*/
	/*invalid address family*/
	do_func_call("lcoalhost", NULL, 0, AF_SNA, 0, 0, EAI_FAMILY);
	/*hard to test for EAI_MEMORY: would have to malloc() until failure, then give some back, then call getaddrinfo and hope that its memory requests would not be satisfied.*/
	/*to test for EAI_NODATA: would have to know of a host with no A record in the DNS*/
#ifdef notdef /*following depends on resolver, sigh*/
	/*believe it or not, there is a registered domain "bar.com", so the
	 * following should generate NO_DATA from the DNS*/
	do_func_call("foo.bar.foo.bar.foo.bar.com", NULL, 0, 0, 0, 0, EAI_NODATA);
#endif
	/*no hostname, no service name*/
	do_func_call(NULL, NULL, 0, 0, 0, 0, EAI_NONAME);
	/*invalid hostname (should be interpreted in local default domain*/
	do_func_call("lkjjkhjhghgfgfd", NULL, 0, 0, 0, 0, EAI_NONAME);
	/*invalid service name*/
	do_func_call(NULL, "nosuchservice", 0, 0, 0, 0, EAI_NONAME);
	/*service valid but not supported for socket type*/
	do_func_call("localhost", "telnet", 0, 0, SOCK_DGRAM, 0, EAI_SERVICE);
	/*service valid but not supported for socket type*/
	do_func_call("localhost", "tftp", 0, 0, SOCK_STREAM, 0, EAI_SERVICE);
	/*invalid socket type*/
	do_func_call("localhost", NULL, 0, AF_INET, SOCK_SEQPACKET, 0, EAI_SOCKTYPE);
	do_func_call("localhost", NULL, 0, AF_INET, SOCK_SEQPACKET, 0, EAI_SOCKTYPE);
	/*EAI_SYSTEM not generated by my implementation*/
}

/*do function call*/
static void do_func_call(const char *host, const char *serv, int flags, int family, int socktype, int protocol, int exprc){
	int rc;
	struct addrinfo hints, *res;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = flags;
	hints.ai_family = family;
	hints.ai_socktype = socktype;
	hints.ai_protocol = protocol;

	rc = getaddrinfo(host, serv, &hints, &res);
	if(rc != exprc){
		printf("expected return = %d (%s),\nactual return = %d (%s)\n", exprc, gai_strerror(exprc), rc, gai_strerror(rc));
		if(host != NULL)
			printf("	host = %s\n", host);
		if(serv != NULL)
			printf("	serv = %s\n", serv);
		printf("  flags = %d, family = %s, socktype = %s, protocol = %d\n", flags, str_fam(family), str_sock(socktype), protocol);
		exit(2);
	}
}

static const char*str_fam(int family){
#ifdef	IPv4
	if(family == AF_INET)
		return("AF_INET");
#endif
#ifdef	IPv6
	if(family == AF_INET6)
		return("AF_INET6");
#endif
#ifdef	UNIXdomain
	if(family == AF_LOCAL)
		return("AF_LOCAL");
#endif
	return("<unknown family>");
}

static const char*str_sock(int socktype){
	switch(socktype){
		case SOCK_STREAM:
			return "SOCK_STREAM";
		case SOCK_DGRAM:
			return "SOCK_DGRAM";
		case SOCK_RAW:
			return "SOCK_RAW";
#ifdef SOCK_RDM
		case SOCK_RDM:
			return "SOCK_RDM";
#endif
#ifdef SOCK_SEQPACKET
		case SOCK_SEQPACKET:
			return "SOCK_SEQPACKET";
#endif
		default:
			return "<unknown socktype>";
	}
}

/*command usage*/
static void usage(const char *msg){
	printf(
"usage: testaddrinfo [ options ]\n"
"options: -h <host>	(can be hostname or address string)\n"
"	 -s <service>  (can be service name or decimal port number)\n"
"	 -c	AI_CANONICAL flag\n"
"	 -p	AI_PASSIVE flag\n"
"	 -l N	loop N times (check for memory leaks with ps)\n"
"	 -f X	address family, X = inet, inet6, unix\n"
"	 -r X  protocol, X = tcp, udp, ... or number e.g. 6, 17, ...\n"
"	 -v	verbose\n"
"	 -e	only do test of error returns (no options required)\n"
" without -e,	one or both of <host> and <service> must be specified.\n"
);
	
	if(msg[0] != 0)
		printf("%s\n", msg);
	exit(1);
}

