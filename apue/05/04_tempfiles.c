/*
 * =====================================================================================
 *
 *       Filename:  04_tempfiles.c
 *
 *    Description:  tempfiles
 *
 *        Version:  1.0
 *        Created:  04/30/13 21:37:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

int main(void){
	char name[L_tmpnam], line[MAXLINE];
	FILE *fp;
	printf("L_tmpnam = %d,first tmpnam = %s\n",L_tmpnam,tmpnam(NULL));

	tmpnam(name);/*second temp name*/
	printf("%s\n", name);
	
	/*create temp file*/
	if((fp = tmpfile()) == NULL)
		err_sys("tmpfile error");
	
	/*write to temp file*/
	fputs("one line of output\n", fp);
	rewind(fp);/*then read it back*/
	
	if(fgets(line, sizeof(line), fp)==NULL)
		err_sys("fgets error");
	fputs(line, stdout);/*print the line we wrote*/

	exit(0);
}

