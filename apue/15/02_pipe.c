/*
 * =====================================================================================
 *
 *       Filename:  02_pipe.c
 *
 *    Description:  02 pipe
 *
 *        Version:  1.0
 *        Created:  06/02/13 21:11:36
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

#define DEF_PAGER "/bin/more" /*default pager program*/

int main(int argc, char *argv[]){
	int n;
	int fd[2];
	pid_t pid;

	char *pager, *argv0;
	char line[MAXLINE];
	FILE *fp;

	if(argc != 2){
		err_quit("usage: a.out <pathname>");
	}
	printf("getenv pager:%s\n", getenv("PAGER"));

	if((fp = fopen(argv[1], "r")) == NULL){
		err_sys("can't open %s", argv[1]);
	}
	if(pipe(fd) < 0){
		err_sys("pipe error");
	}

	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid > 0){/*parent*/
		close(fd[0]);/*close read end*/

		/*parent copies arv[1] to pipe*/
		while(fgets(line, MAXLINE, fp) != NULL){
			n = strlen(line);
			if(write(fd[1], line, n) != n)
				err_sys("write error to pipe");
		}
		if(ferror(fp))
			err_sys("fgets error");
		close(fd[1]);/*close write end of pipe for reader*/
		if(waitpid(pid, NULL, 0) < 0){
			err_sys("waitpid error");
		}
		exit(0);
	}else{/*child*/
		close(fd[1]);/*close write end*/
		/*copy read end to STDIN_FILENO*/
		if(fd[0] != STDIN_FILENO){
			if(dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
				err_sys("dup2 error to stdin");
			close(fd[0]);/*don't need this after dup2*/
		}

		/*get arguments for execl()*/
		if((pager = getenv("PAGER")) == NULL){
			pager = DEF_PAGER;
		}else{
			printf("pager:%s\n",pager);/*NULL*/
		}

		if((argv0 = strrchr(pager, '/')) != NULL)
			argv0++;/*step past rightmost slash*/
		else
			argv0 = pager;/*no slash in pager*/
		printf("prog argv0:%s\n",argv0);/*NULL*/

		/*
		while((n = read(STDIN_FILENO, line, MAXLINE)) > 0){
			printf("read : %d\n", n);
			write(STDOUT_FILENO, line, n);
		}
		*/
		/*when exec pager prog, the stdin is the read end.*/
		if(execl(pager, argv0, (char *)0) < 0){
			err_sys("execl error for %s", pager);
		}
	}
	exit(0);
}

