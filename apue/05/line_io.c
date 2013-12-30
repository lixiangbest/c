/*
 * =====================================================================================
 *
 *       Filename:  line_io.c
 *
 *    Description:  line i/o function
 *
 *        Version:  1.0
 *        Created:  04/30/13 15:09:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>
#define LEN 5
int main(void){
	char buf[LEN];
	char m[] = "love";
	puts(m);//will add \n.
	printf("TMP_MAX=%d\n",TMP_MAX);
	while(fgets(buf,LEN,stdin)!=NULL){
		fputs(buf,stdout);
		printf("\n");
	}
	if(ferror(stdin)){
		perror("get line error!");
	}
	return 0;
}

