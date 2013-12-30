/*
 * =====================================================================================
 *
 *       Filename:  06_opendata.c
 *
 *    Description:  open data
 *
 *        Version:  1.0
 *        Created:  05/06/13 22:59:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>

#define DATAFILE "datafile"

FILE *open_data(void){
	FILE *fp;
	char databuf[BUFSIZ];/*setvbuf makes this the stdio buffer*/
	
	if((fp=fopen(DATAFILE, "r")) == NULL)
		return NULL;
	if(setvbuf(fp, databuf, _IOLBF, BUFSIZ) != 0)
		return NULL;
	return(fp);/*error*/
}

int main(){
	FILE *fp;
	printf("BUFSIZ=%d\n", BUFSIZ);
	fp = open_data();
	return 0;
}

