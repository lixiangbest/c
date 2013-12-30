/*
 * =====================================================================================
 *
 *       Filename:  getpos.c
 *
 *    Description:  get pos.
 *
 *        Version:  1.0
 *        Created:  04/30/13 17:27:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[]){
	FILE *fp;
	char buf[5];
	if(argc!=2){
		printf("argc must be 2.error!");
		exit(0);
	}
	fp = fopen(argv[1],"r");
	printf("fgets=%s\n",fgets(buf,5,fp));
	printf("ftell=%ld\n",ftell(fp));
	fseek(fp,3,SEEK_CUR);
	printf("after seek fgets = %s\n",fgets(buf,5,fp));
	rewind(fp);
	printf("after rewind fgets=%s\n",fgets(buf,5,fp));
	return 0;
}

