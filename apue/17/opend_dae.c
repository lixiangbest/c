/*
 * =====================================================================================
 *
 *       Filename:  opend_dae.c
 *
 *    Description:  open fd server running as daemon.
 *
 *        Version:  1.0
 *        Created:  06/15/13 17:52:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
/*start opend.h*/
#include "apue.h"
#include<errno.h>
#include<sys/time.h>
#include<sys/select.h>
#include<poll.h>

#if !defined(BSD) && !defined(MACOS)
#include<stropts.h>
#endif

#include<fcntl.h>

#define CS_OPEN "/home/suncco/c/apue/17/opend_dae.so" /*well-known name*/
#define CL_OPEN "open" /*client's request for server*/

/*extern int debug;*//*nonzero if interactive (not daemon)*/
/*extern char errmsg[];*//*error message string to return to client*/
/*extern int oflag;*//*open() flag: O_xxx ...*/
/*extern char *pathname;*//*of file to open() for client*/

typedef struct{ /*one Client struct per connected client*/
	int fd; /*fd, or -1 if available*/
	uid_t uid;
}Client;

/*extern Client *client;*//* ptr to malloc'ed array */
/*extern int client_size;*//* fd, or -1 if available */

int cli_args(int, char **);
int client_add(int, uid_t);
void client_del(int);
void loop(void);
void request(char *, int, int, uid_t);
/*end opend.h*/

#include<syslog.h>

int debug, oflag, client_size, log_to_stderr;
char errmsg[MAXLINE];
char *pathname;
Client *client = NULL;

int main(int argc, char *argv[]){
	int c;
	/*
	int read;
	char buf[MAXLINE];
	*/
	FILE *fp;

	if((fp = fopen("opend.log", "a+")) == NULL){
		err_sys("open error");
	}

	log_open("open.serv", LOG_PID, LOG_USER);

	opterr = 0;/*don't want getopt() writing to stderr*/
	while((c = getopt(argc, argv, "d")) != EOF){
		switch(c){
			case 'd':	/*debug*/
				debug = log_to_stderr = 1;
				break;

			case '?':
				err_quit("unrecognized option: -%c", optopt);
		}
	}
	if(debug == 0)
		daemonize("opend");
	
	loop();/*never returns*/

	return 0;
}

#define NALLOC 10 /*#client structs to alloc/realloc for*/

/*alloc more entries in the client[] array*/
static void client_alloc(void){
	int i;

	if(client == NULL)
		client = malloc(NALLOC * sizeof(Client));
	else
		client = realloc(client, (client_size+NALLOC)*sizeof(Client));
	if(client == NULL) err_sys("can't alloc for client array");

	/*Initialize the new entries*/
	for(i = client_size; i < client_size + NALLOC; i++)
		client[i].fd = -1;/*fd of -1 means entry available*/

	client_size += NALLOC;
}

/*called by loop() when connection request from a new client arrives.*/
int client_add(int fd, uid_t uid){
	int i;

	if(client == NULL) client_alloc();/*first time we're called*/

again:
	for(i = 0; i < client_size; i++){
		/*find an available entry*/
		if(client[i].fd == -1){
			client[i].fd = fd;
			client[i].uid = uid;
			return i;/*return index in client[] array*/
		}
	}
	/*client array full, time to realloc for more*/
	client_alloc();
	goto again;/*and search again (will work this time)*/
}

/*Called by loop() when we're done with a client.*/
void client_del(int fd){
	int i;

	for(i = 0; i < client_size; i++){
		if(client[i].fd == fd){
			client[i].fd = -1;
			return;
		}
	}
	log_quit("can't find client entry for fd %d", fd);
}

/*loop select*/
void loop(){
	int i, n, maxfd, maxi, listenfd, clifd, nread;
	char buf[MAXLINE];
	uid_t uid;
	fd_set rset, allset;

	FD_ZERO(&allset);

	/*obtain fd to listen for client requests on*/
	if((listenfd = serv_listen(CS_OPEN)) < 0)
		log_sys("serv_listen error");
	FD_SET(listenfd, &allset);
	maxfd = listenfd;
	maxi = -1;

	for(;;){
		rset = allset;/*rset gets modified each time around*/
		if((n = select(maxfd + 1, &rset, NULL, NULL, NULL)) < 0)
			log_sys("select error");
		
		if(FD_ISSET(listenfd, &rset)){
			/*accept new client request*/
			if((clifd = serv_accept(listenfd, &uid)) < 0)
				log_sys("serv_accept error: %d", clifd);
			i = client_add(clifd, uid);
			FD_SET(clifd, &allset);
			if(clifd > maxfd)
				maxfd = clifd;/*max fd for select()*/
			if(i > maxi)
				maxi = i;/*max fd for select()*/
			log_msg("new connection: uid %d, fd %d", uid, clifd);
			continue;
		}
		for(i=0; i<=maxi; i++){/*go through client[] array*/
			if((clifd = client[i].fd) < 0)
				continue;
			if(FD_ISSET(clifd, &rset)){
				/*read argument buffer from client*/
				if((nread = read(clifd, buf, MAXLINE)) < 0){
					log_sys("read error on fd %d", clifd);
				}else if(nread == 0){
					log_msg("closed: uid %d, fd %d", client[i].uid, clifd);
					client_del(clifd);/*client has closed cxn*/
					FD_CLR(clifd, &allset);
					close(clifd);
				}else{/*process client's request*/
					request(buf, nread, clifd, client[i].uid);
				}
			}
		}
	}
}

/*loop poll*/
void loop_poll(){
	int i, maxi, listenfd, clifd, nread;
	char buf[MAXLINE];
	uid_t uid;
	struct pollfd *pollfd;

	if((pollfd = malloc(open_max() * sizeof(struct pollfd))) == NULL)
		err_sys("malloc error");

	/*obtain fd to listen for client requests on*/
	if((listenfd = serv_listen(CS_OPEN)) < 0)
		log_sys("serv_listen error");
	client_add(listenfd, 0);/*we use [0] for listenfd*/
	pollfd[0].fd = listenfd;
	pollfd[0].events = POLLIN;
	maxi = 0;

	for(;;){
		if(poll(pollfd, maxi + 1, -1) < 0)
			log_sys("poll error");
		
		if(pollfd[0].revents & POLLIN){
			/*accept new client request*/
			if((clifd = serv_accept(listenfd, &uid)) < 0)
				log_sys("serv_accept error: %d", clifd);
			i = client_add(clifd, uid);
			pollfd[i].fd = clifd;
			pollfd[i].events = POLLIN;
			if(i > maxi)
				maxi = i;/*max fd for select()*/
			log_msg("new connection: uid %d, fd %d", uid, clifd);
		}
		for(i=1; i<=maxi; i++){/*go through client[] array*/
			if((clifd = client[i].fd) < 0)
				continue;
			if(pollfd[i].revents & POLLHUP){
				goto hungup;
			}else if(pollfd[i].revents & POLLIN){
				/*read argument buffer from client*/
				if((nread = read(clifd, buf, MAXLINE)) < 0){
					log_sys("read error on fd %d", clifd);
				}else if(nread == 0){
hungup:
					log_msg("closed: uid %d, fd %d", client[i].uid, clifd);
					client_del(clifd);/*client has closed cxn*/
					pollfd[i].fd = -1;
					close(clifd);
				}else{/*process client's request*/
					request(buf, nread, clifd, client[i].uid);
				}
			}
		}
	}
}

void request(char *buf, int nread, int clifd, uid_t uid){
	int newfd;/*fd will be sent to client.*/

	if(buf[nread-1] != 0){
		sprintf(errmsg, "request from uid %d not null terminated: %*.*s\n", uid, nread, nread, buf);
		send_err(clifd, -1, errmsg);
		return;
	}
	log_msg("request: %s, from uid %d", buf, uid);
	
	/*parse the arguments, set options*/
	if(buf_args(buf, cli_args) < 0){
		send_err(clifd, -1, errmsg);
		log_msg(errmsg);
		return;
	}
	if((newfd = open(pathname, oflag)) < 0){
		sprintf(errmsg, "can't open %s: %s\n", pathname, strerror(errno));
		send_err(clifd, -1, errmsg);
		log_msg(errmsg);
		return;
	}
	if(send_fd(clifd, newfd) < 0)/*send the descriptor*/
		err_sys("send_fd error");
	log_msg("sent fd %d over fd %d for %s", newfd, clifd, pathname);
	close(newfd);/*we're done with descriptor*/
}

/*
 * This function is called by buf_args(), which is called by
 * request(). buf_args() has broken up the client's buffer
 * into an argv[]-style array, which we now process.
 */
int cli_args(int argc, char **argv){
	if(argc != 3 || strcmp(argv[0], CL_OPEN) != 0){
		strcpy(errmsg, "usage: <pathname> <oflag>\n");
		return -1;
	}
	pathname = argv[1];/*save ptr to pathname to open*/
	oflag = atoi(argv[2]);
	return 0;
}
