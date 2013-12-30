/*************************************************************************
	> File Name: unixdgcli01.c
	> Description: 
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月14日 星期六 09时24分23秒
 ************************************************************************/
#include "unp.h"

int main(int argc, char **argv){
	int sockfd;
	struct sockaddr_un cliaddr, servaddr;
	char tmp_file[] = "tmp_XXXXXX";
	
	if(mkstemp(tmp_file)==-1){
		err_quit("Create temp file fail!");
	}
	unlink(tmp_file);/*unlink or bind will error.*/

	sockfd = Socket(AF_LOCAL, SOCK_DGRAM, 0);
	
	bzero(&cliaddr, sizeof(cliaddr));/*bind an address for us*/
	cliaddr.sun_family = AF_LOCAL;
	strcpy(cliaddr.sun_path, tmp_file);
	
	Bind(sockfd, (SA*)&cliaddr, sizeof(cliaddr));
	
	bzero(&servaddr, sizeof(servaddr));/*fill in server's address*/
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UNIXDG_PATH);

	dg_cli(stdin, sockfd, (SA*)&servaddr, sizeof(servaddr));

	unlink(tmp_file);

	return 0;
}
