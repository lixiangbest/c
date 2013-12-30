/*
 * =====================================================================================
 *
 *       Filename:  mycp.c
 *
 *    Description:  copy
 *
 *        Version:  1.0
 *        Created:  04/29/13 18:06:36
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

int main(void){
	char buf;/*copy a char*/
	while(read(STDIN_FILENO,&buf,1)){
		if(buf!='\0'){
			write(STDOUT_FILENO,&buf,1);
		}
	}
	return 0;
}

