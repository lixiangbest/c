/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  test the open file descriptor.
 *
 *        Version:  1.0
 *        Created:  04/20/13 16:49:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<limits.h>

int main(void){
	int desc;
	close(STDERR_FILENO);/*close,look the desc change.*/
	desc = open("linux.mk",O_RDONLY);
	//close(STDERR_FILENO);/*close,look the desc change.*/
	printf("STDIN_FILENO=%d,STDOUT_FILENO=%d,STDERR_FILENO=%d\n",STDIN_FILENO,STDOUT_FILENO,STDERR_FILENO);
	printf("f_desc=%d\n",desc);
	printf("%d,%d,%d,O_RDONLY|O_WRONLY|O_RDWR=%d",O_RDONLY,O_WRONLY,O_RDWR,O_RDONLY|O_WRONLY|O_RDWR);

#ifdef _SC_V6_ILP32_OFF32
	printf("\nILP32_OFF32=%ld\n",sysconf(_SC_V6_ILP32_OFF32));
#else
	printf("no symbol for ILP32_OFF32\n");
#endif

}
