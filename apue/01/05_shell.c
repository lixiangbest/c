/*
 * =====================================================================================
 *
 *       Filename:  05_shell.c
 *
 *    Description:  child process.
 *
 *        Version:  1.0
 *        Created:  04/18/13 20:44:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */

#include "apue.h"
#include<sys/wait.h>

int main(void){
	char buf[MAXLINE];/*from apue.h*/
	pid_t pid;
	int status;
	/*print prompt (printf requires %% to print %)*/
	printf("%% ");
	/* get a line each time,bufsize-1 length + '\0',
	 * return the buf pointer if run success.
	 * buf include the '\n' and '\0',strlen does not include
	 * '\0'
	 * */
	while(fgets(buf,MAXLINE,stdin)!=NULL){
		if(buf[strlen(buf)-1]!=NULL){
			/*replace newline with null,\0*/
			buf[strlen(buf)-1] = 0;
		}
		/*fork an process*/
		if((pid = fork())<0){
			err_sys("fork error");
		}else if(pid==0){/*child*/
			execlp(buf, buf, (char*)0);
			err_ret("couldn't execute: %s", buf);
			exit(127);
		}
		printf("pid=%d\n",pid);/*child process id when return to parent process.*/	
		/*parent*/
		if((pid=waitpid(pid,&status,0))<0){
			err_sys("waitpid error");
		}
		/*enter the shell command.*/
		printf("status=%d,pid=%d\n%% ",status,pid);
	}

	exit(0);
}

