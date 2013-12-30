/*************************************************************************
	> File Name: unixstrcli02.c
	> Description: 
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月17日 星期二 13时58分36秒
 ************************************************************************/
#include "unp.h"

static ssize_t write_cred(int, void *, size_t);

int main(int argc, char **argv){
	int sockfd;
	struct sockaddr_un servaddr;
	char *buf = "Hello";

	sockfd = Socket(AF_LOCAL, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UNIXSTR_PATH);

	Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));

	if(write_cred(sockfd, buf, 5) < 0){
		err_sys("write cred error");
	}

	return 0;
}

static ssize_t write_cred(int fd, void *ptr, size_t nbytes){
	struct msghdr msg;
	struct iovec iov[1];
	union{
		struct cmsghdr cm;
		char control[CMSG_SPACE(sizeof(struct ucred))];
	}control_un;
	struct cmsghdr *cmptr;
	struct ucred *ucptr;

	msg.msg_control = control_un.control;
	msg.msg_controllen = sizeof(control_un.control);

	cmptr = CMSG_FIRSTHDR(&msg);
	cmptr->cmsg_len = CMSG_LEN(sizeof(struct ucred));
	cmptr->cmsg_level =	SOL_SOCKET;
	cmptr->cmsg_type = SCM_CREDENTIALS;

	ucptr = (struct ucred *)CMSG_DATA(cmptr);
	ucptr->pid = getpid();
	ucptr->uid = getuid();
	ucptr->gid = getgid();

	msg.msg_name = NULL;
	msg.msg_namelen = 0;

	iov[0].iov_base = ptr;
	iov[0].iov_len = nbytes;
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;

	return (sendmsg(fd, &msg, 0));

}
