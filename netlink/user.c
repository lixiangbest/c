/*************************************************************************
	> File Name: user.c
	> Description: netlink user mode. 
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月26日 星期四 09时32分40秒
 ************************************************************************/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<asm/types.h>
#include<linux/netlink.h>

#define MAX_MSGSIZE 1024
struct sockaddr_nl src_addr, dest_addr;
struct msghdr msg;
struct nlmsghdr *nlhdr = NULL;
struct iovec iov;
int sockfd;
char buffer[] = "Hello, Taylor!";

int main(int argc, char *argv[]){
	sockfd = Socket(AF_NETLINK, SOCK_RAW, 17);//17 is our defined protocol type.
	
	memset(&src_addr, 0, sizeof(src_addr));
	src_addr.nl_family = AF_NETLINK;
	src_addr.nl_pid = getpid();//self pid
	src_addr.nl_groups = 0;

	if( bind(sockfd, (struct sockaddr *)&src_addr, sizeof(struct sockaddr_nl)) == -1 ){
		perror("bind");
		close(sockfd);
	}

	memset(&dest_addr, 0, sizeof(dest_addr));
	dest_addr.nl_family = AF_NETLINK;
	dest_addr.nl_pid = 0;//for kernel set 0
	dest_addr.nl_groups = 0;

	memset(&msg, 0, sizeof(msg));
	msg.msg_name = (void *)&(dest_addr);
	msg.msg_namelen = sizeof(dest_addr);

	nlhdr = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_MSGSIZE));
	/*Fill the netlink message datapart*/
	strcpy(NLMSG_DATA(nlhdr), buffer);
	/*Fill the netlink message header*/
	nlhdr->nlmsg_len = NLMSG_LENGTH(strlen(buffer));
	nlhdr->nlmsg_pid = getpid();/*self pid*/
	nlhdr->nlmsg_flags = 0;

	iov.iov_base = (void *)nlhdr;
	iov.iov_len = nlhdr->nlmsg_len;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;

	printf("Start send messages!\n");
	sendmsg(sockfd, &msg, 0);

	//Recv message come from kernel
	memset(nlhdr, 0, NLMSG_SPACE(MAX_MSGSIZE));
	printf("Wait recv messages!\n");
	recvmsg(sockfd, &msg, 0);
	printf("Received messages!Data part is:%s\n", NLMSG_DATA(nlhdr));
	
	close(sockfd);
	return 0;
}

