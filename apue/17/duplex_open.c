/*
 * =====================================================================================
 *
 *       Filename:  duplex_open.c
 *
 *    Description:  duplex intercommunication open.
 *    				Implementation of duplex pipe stream.
 *
 *        Version:  1.0
 *        Created:  06/15/13 21:06:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#ifndef _DPOPEN_H
#define _DPOPEN_H

#include<stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

FILE *dpopen(const char *command);
int dpclose(FILE *stream);
int dphalfclose(FILE *stream);

#ifdef __cplusplus
}
#endif

#endif /*_DPOPEN_H*/

#include<errno.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>

#ifdef _REENTRANT
#include<pthread.h>
static pthread_mutex_t chain_mtx = PTHREAD_MUTEX_INITIALIZER;
#endif

/*Struct to store duplex-pipe-specific information.*/
struct dpipe_chain{
	FILE *stream;/*pointer to the duplex pipe stream*/
	pid_t pid;/*process ID of the command*/
	struct dpipe_chain *next;/*pointer to the next one in chain*/
};

/*Typedef to make the struct easier to use.*/
typedef struct dpipe_chain dpipe_t;

/*Header of the chain of opened duplex pipe streams*/
static dpipe_t *chain_hdr;

/*
 * Init a duplex pipe stream from/to a process.
 * Like popen, all previously dpopen'd pipe streams will be closed
 * in the child process.
 *
 * @param command		the command to execute on \c sh
 * @return 				a pointer to an open stream on successful
 * 						completion; \c NULL otherwise
 */
FILE *dpopen(const char *command){
	int fd[2], parent, child, nread;
	pid_t pid;
	FILE *stream;
	dpipe_t *chain;
	char buf[80];

	/*Create a duplex pipe using the BSD socketpair call*/
	if(socketpair(AF_UNIX, SOCK_STREAM, 0, fd) < 0)
		return NULL;
	parent = fd[0];
	child = fd[1];

	/*Fork the process and check whether it is successful*/
	if((pid = fork()) < 0){
		close(parent);
		close(child);
		return NULL;
	}

	if(pid == 0){/*child*/
		/*Close the other end*/
		close(parent);
		/*Duplicate to stdin and stdout,first close STDIN_FILENO, then STDIN_FILENO pointer to child fd.STDIN_FILENO don't point to the tty device.*/
		if(child != STDIN_FILENO)
			if(dup2(child, STDIN_FILENO) < 0){
				close(child);
				return NULL;
			}
		if(child != STDOUT_FILENO)
			if(dup2(child, STDOUT_FILENO) < 0){
				close(child);
				return NULL;
			}
		/*Close this end too after it is duplicated to standard I/O*/
		close(child);
		/*printf("in child pid:%d\n", pid);*/
		/*Close all previously opened pipe streams, as popen does*/
		for(chain = chain_hdr; chain != NULL; chain = chain->next){
			printf("previous closing child chain->pid:%d\n", chain->pid);
			close(fileno(chain_hdr->stream));
		}
		
		/*output string.*/
		/*while((nread = read(STDIN_FILENO, buf, 80)) != 0)*/
		/*
		nread = read(STDIN_FILENO, buf, 80);
		write(STDOUT_FILENO, buf, nread);
		*/

		/*Execute the command via sh*/
		execl("/bin/sh", "sh", "-c", command, NULL);
		/*Exit the child process if execl fails*/
		_exit(127);
	}else{/*parent*/
		/*close the other end*/
		close(child);
		/*Open a new stream with the file descriptor of the pipe*/
		stream = fdopen(parent, "r+");
		if(stream == NULL){
			close(parent);
			return NULL;
		}
		/*Allocate memory for the dpipe_t struct*/
		chain = (dpipe_t *)malloc(sizeof(dpipe_t));
		if(chain == NULL){
			fclose(stream);
			return NULL;
		}
		/*Store necessary info for dpclose, and adjust chain header*/
		chain->stream = stream;
		chain->pid = pid;/*pid is the child process id.*/
#ifdef _REENTRANT
		printf("_REENTRANT:%d\n", _REENTRANT);
		pthread_mutex_lock(&chain_mtx);
#endif
		chain->next = chain_hdr;
		chain_hdr = chain;
#ifdef _REENTRANT
		pthread_mutex_unlock(&chain_mtx);
#endif
		/*Successfully return here*/
		return stream;
	}
}

/*
 * Closes a duplex pipe stream from/to a process.
 *
 * @param stream	pointer to a pipe stream returned from a previous #dpopen call
 * @return		the exit status of the command if successful; \c -l if an error occurs
 */
int dpclose(FILE *stream){
	int status;
	pid_t pid, wait_res;
	dpipe_t *cur;
	dpipe_t **ptr;

	/*Search for the stream starting from chain header*/
#ifdef _REENTRANT
	pthread_mutex_lock(&chain_mtx);
#endif
	ptr = &chain_hdr;
	while((cur = *ptr) != NULL){/*Not end of chain*/
		printf("dpclose cur->pid:%d\n", cur->pid);
		if(cur->stream == stream){/*Stream found*/
			pid = cur->pid;
			*ptr = cur->next;
#ifdef _REENTRANT
			pthread_mutex_unlock(&chain_mtx);
#endif
			free(cur);
			if(fclose(stream) != 0)	return -1;
			do{
				wait_res = waitpid(pid, &status, 0);
			}while(wait_res == -1 && errno == EINTR);
			if(wait_res == -1) return -1;
			return status;
		}
		ptr = &cur->next;/*Check next*/
	}
#ifdef _REENTRANT
	pthread_mutex_unlock(&chain_mtx);
#endif
	errno = EBADF;/*If the given stream is not found*/
	return -1;
}

/*
 * Flushes the buffer and sends \c EOF to the process at the other end
 * of the duplex pipe stream.
 *
 * @param stream pointer to a pipe stream returned from a previous #dpopen call
 * @return \c 0 if successful; \c -1 if an error occurs
 */
int dphalfclose(FILE *stream){
	/*Ensure all data are flushed*/
	if(fflush(stream) == EOF)
		return -1;
	/*Close pipe for writing*/
	return shutdown(fileno(stream), SHUT_WR);
}

#define MAXLINE 80

int main(){
	char line[MAXLINE];
	FILE *fp;
	printf("cur pid:%d\n", getpid());
	dpopen("cat");
	fp = dpopen("sort");
	if(fp == NULL){
		perror("dpopen error");
		exit(1);
	}
	fprintf(fp, "orange\n");
	fprintf(fp, "apple\n");
	fprintf(fp, "pear\n");
	if(dphalfclose(fp) < 0){
		perror("dphalfclose error");
		exit(1);
	}
	for(;;){
		if(fgets(line, MAXLINE, fp) == NULL)	break;
		fputs(line, stdout);
	}
	dpclose(fp);
	return 0;
}
