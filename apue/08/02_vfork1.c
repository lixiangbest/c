/*
 * =====================================================================================
 *
 *       Filename:  02_vfork1.c
 *
 *    Description:  vfork usage.
 *
 *        Version:  1.0
 *        Created:  05/08/13 01:02:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

int glob = 6;/*external variable in initialized data*/
char buf[] = "a write to stdout\n";

int main(void){
	int var;/*automatic variable on the stack*/
	pid_t pid;
	char mybuf[MAXLINE];
	var = 88;
	int i;
	/*printf("strlen=%d,sizeof=%d\n",strlen(buf),sizeof(buf));*/
	if(write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
		err_sys("write error");
	printf("before fork\n");/*we don't flush stdout*/

	if((pid=vfork()) < 0){
		err_sys("fork error");
	}else if(pid==0){/*child*/
		glob++;/*modify parent's variables*/
		var++;
		fclose(stdout);/*parent will has no print*/
		_exit(0);
	}
	i = printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
	sprintf(mybuf, "%d\n", i);
	write(STDOUT_FILENO, mybuf, strlen(mybuf));
	exit(0);
}

