/*************************************************************************
	> File Name: strecho.c
	> Description: 
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月17日 星期二 08时32分33秒
 ************************************************************************/
#include "unp.h"

ssize_t read_cred(int, void *, size_t, struct cmsgcred *);

void str_echo(int sockfd){
	ssize_t n;
	int i;
	char buf[MAXLINE];
	struct ucred cred;

again:	
	while( (n = read_cred(sockfd, buf, MAXLINE, &cred)) >0){
		buf[5] = '\0';
		printf("read data = %s\n", buf);
		printf("PID of sender = %d\n", cred.pid);
		printf("real user ID = %d\n", cred.uid);
		printf("real group ID = %d\n", cred.gid);
		printf("\n");
		
		Writen(sockfd, buf, n);
	}

	if( n < 0 && errno == EINTR)
		goto again;
	else if( n < 0 )
		err_sys("str_echo: read error");
}
