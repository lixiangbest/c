/*************************************************************************
	> File Name: unixbind.c
	> Description: 
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月14日 星期六 02时30分16秒
 ************************************************************************/
#include "unp.h"

int main(int argc, char **argv){
	int sockfd;
	socklen_t len;
	struct sockaddr_un addr1, addr2;

	if(argc != 2){
		err_quit("usage: unixbind <pathname>");
	}
	sockfd = Socket(AF_LOCAL, SOCK_STREAM, 0);
	
	unlink(argv[1]);/*OK if this fails*/

	bzero(&addr1, sizeof(addr1));
	addr1.sun_family = AF_LOCAL;
	strncpy(addr1.sun_path, argv[1], sizeof(addr1.sun_path)-1);
	Bind(sockfd, (SA *)&addr1, SUN_LEN(&addr1));
	
	len = sizeof(addr2);
	Getsockname(sockfd, (SA*)&addr2, &len);
	printf("SUN_LEN = %d, bound name = %s, returned len = %d\n", SUN_LEN(&addr1), addr2.sun_path, len);

	exit(0);
}
