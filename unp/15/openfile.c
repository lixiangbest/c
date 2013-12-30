/*************************************************************************
	> File Name: openfile.c
	> Description: 
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月16日 星期一 19时13分50秒
 ************************************************************************/
#include "unp.h"

int main(int argc, char **argv){
	int fd;

	if(argc != 4)
		err_quit("openfile <sockfd#> <filename> <mode>");

	if( (fd = open(argv[2], atoi(argv[3]))) < 0)
		exit( (errno > 0) ? errno:255 );

	if( write_fd(atoi(argv[1]), "", 1, fd) < 0)
		exit( (errno > 0) ? errno:255 );
	
	exit(0);
}
