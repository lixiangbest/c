/*
 * =====================================================================================
 *
 *       Filename:  03_ctermid.c
 *
 *    Description:  my ctermid function implement.
 *
 *        Version:  1.0
 *        Created:  06/18/13 22:06:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

static char ctermid_name[L_ctermid];

char *my_ctermid(char *str){
	if(str == NULL) str = ctermid_name;
	return(strcpy(str, "/dev/tty"));/*strcpy() returns str*/
}

int main(){
	char term[L_ctermid];
	char my_term[L_ctermid];
	char *ptr;
	struct termios tos;

	printf("cfgetispeed = 0x%x, cfgetospeed = 0x%x\n", cfgetispeed(&tos), cfgetospeed(&tos));
	
	ptr = ctermid(term);
	printf("L_ctermid = 0x%x, ptr = %s\n", L_ctermid, ptr);

	ptr = my_ctermid(my_term);
	printf("L_ctermid = 0x%x, ptr = %s\n", L_ctermid, ptr);

	printf("isatty(STDIN_FILENO) = %d, ttyname(STDIN_FILENO) = %s\n", isatty(STDIN_FILENO), ttyname(STDIN_FILENO));
	return 0;
}
