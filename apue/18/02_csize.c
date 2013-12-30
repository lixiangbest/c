/*
 * =====================================================================================
 *
 *       Filename:  02_csize.c
 *
 *    Description:  tcgetattr and tcsetattr
 *
 *        Version:  1.0
 *        Created:  06/17/13 23:09:48
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

int main(void){
	struct termios term;

	if(tcgetattr(STDIN_FILENO, &term) < 0){
		err_sys("tcgetattr error");
	}

	printf("^[c");
	printf("^[D");
	printf("^[[0;33mI wish\n");
	printf("^[[0;33mI wish\n");
	printf("^[[2K^[[1G");
	printf("^[[1;32mI wish\n");
	printf("^[[0;0m\n");
	
	printf("CSIZE=0x%x,c_cflag=0x%x\n", CSIZE, term.c_cflag);
	switch(term.c_cflag & CSIZE){
			case CS5:
				printf("CS5:0x%x 5 bits/byte\n", CS5);break;
			case CS6:
				printf("CS6:0x%x 6 bits/byte\n", CS6);break;
			case CS7:
				printf("CS7:0x%x 7 bits/byte\n", CS7);break;
			case CS8:
				printf("CS8:0x%x 8 bits/byte\n", CS8);break;
			default:
				printf("unknown bits/byte\n");
	}

	term.c_cflag &= ~CSIZE;/*zero out the bits*/
	term.c_cflag |= CS8;/*set 8 bits/byte*/
	if(tcsetattr(STDIN_FILENO, TCSANOW, &term) < 0)
		err_sys("tcsetattr error");
	
	printf("like 6 bits/byte %d\n", 1);

	exit(0);
}
