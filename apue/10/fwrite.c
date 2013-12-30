/*
 * =====================================================================================
 *
 *       Filename:  fwrite.c
 *
 *    Description:  fwrite
 *
 *        Version:  1.0
 *        Created:  05/20/13 23:34:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

static void sig_alarm(int signo){
	printf("catch alarm signal %d\n", signo);
	return;
}

int main(){
	FILE *stream;
	char buf[102400] = {'a','b','c'};
	
	if(signal(SIGALRM, sig_alarm) < 0){
		err_sys("sigalrm error.");
	}

	alarm(1);
	if((stream=fopen("test.txt","wb"))==NULL){
		fprintf(stderr, "Can not open output file.\n");
		return 1;
	}
	printf("begin to write..\n");
	printf("%d,write done.\n ",fwrite(buf, 102400, 1, stream));
	fclose(stream);
	return 0;
}

