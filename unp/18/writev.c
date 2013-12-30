/*************************************************************************
	> File Name: writev.c
	> Description: writev function usage. 
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月26日 星期四 07时10分26秒
 ************************************************************************/
#include "unp.h"

int main(int argc, char **argv){
	char part0[] = "[";
	char part1[] = "This is from writev";
	char part2[] = "]\n";
	struct iovec iov[3];
	
	iov[0].iov_base = part0;
	iov[0].iov_len = strlen(part0);
	iov[1].iov_base = part1;
	iov[1].iov_len = strlen(part1);
	iov[2].iov_base = part2;
	iov[2].iov_len = strlen(part2);
	writev(STDOUT_FILENO, iov, 3);

	return 0;
}

