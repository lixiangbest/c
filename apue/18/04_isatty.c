/*
 * =====================================================================================
 *
 *       Filename:  04_isatty.c
 *
 *    Description:  isatty function implement.
 *
 *        Version:  1.0
 *        Created:  06/18/13 22:49:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<termios.h>

int my_isatty(int fd){
	struct termios ts;
	return(tcgetattr(fd, &ts) != -1);/*true if no error (is a tty)*/
}

int main(){
	printf("isatty fd 0: %s\n", isatty(0) ? "tty" : "not a tty");
	printf("isatty fd 1: %s\n", isatty(1) ? "tty" : "not a tty");
	printf("isatty fd 2: %s\n", isatty(2) ? "tty" : "not a tty");
	
	printf("my_isatty fd 0: %s\n", my_isatty(0) ? "tty" : "not a tty");
	printf("my_isatty fd 1: %s\n", my_isatty(1) ? "tty" : "not a tty");
	printf("my_isatty fd 2: %s\n", my_isatty(2) ? "tty" : "not a tty");
	return 0;
}

