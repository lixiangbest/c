/*
 * =====================================================================================
 *
 *       Filename:  opend.c
 *
 *    Description:  open fd server.
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
#include<fcntl.h>

#define CL_OPEN "open" /*client's request for server*/

/*extern char errmsg[];*//*error message string to return to client*/
/*extern int oflag;*//*open() flag: O_xxx ...*/
/*extern char *pathname;*//*of file to open() for client*/

int cli_args(int, char **);
void request(char *, int, int);
/*end opend.h*/

char errmsg[MAXLINE];
int oflag;
char *pathname;

int main(void){
	int nread;
	char buf[MAXLINE];
	FILE *fp;

	if((fp = fopen("opend.log", "w+")) == NULL){
		err_sys("open error");
	}

	for(;;){/*read arg buffer from client, process request*/
		if((nread = read(STDIN_FILENO, buf, MAXLINE)) < 0){
			err_sys("read error on stream pipe");
		}else if(nread == 0){
			break;/*client has closed the stream pipe*/
		}
		
		/*opend run log*/
		/*write(STDOUT_FILENO, "me\n", 4);*/
		fprintf(fp, "from client buf:%s,len:%d\n", buf, nread);/*client iov:open opentemp 0*/

		request(buf, nread, STDOUT_FILENO);
	}
	exit(0);
}

void request(char *buf, int nread, int fd){
	int newfd;/*fd will be sent to client.*/

	if(buf[nread-1] != 0){
		sprintf(errmsg, "request not null terminated: %*.*s\n", nread, nread, buf);
		send_err(fd, -1, errmsg);
		return;
	}
	if(buf_args(buf, cli_args) < 0){/*parse args & set options*/
		send_err(fd, -1, errmsg);
		return;
	}
	if((newfd = open(pathname, oflag)) < 0){
		sprintf(errmsg, "can't open %s: %s\n", pathname, strerror(errno));
		send_err(fd, -1, errmsg);
		return;
	}
	/*lseek*/
	lseek(newfd,5,SEEK_SET);
	if(send_fd(fd, newfd) < 0)/*send the descriptor*/
		err_sys("send_fd error");
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
