/*
 * =====================================================================================
 *
 *       Filename:  fun.h
 *
 *    Description:  function for test makefile
 *
 *        Version:  1.0
 *        Created:  10/23/12 20:22:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include"defs.h"

void you_printf(const char*fmt,va_list ap){
	char buf[Maxline];
	vsprintf(buf,fmt,ap);
	printf("vsp:%s;\n",buf);
	sprintf(buf+strlen(buf)-1,": %s","lixiang");
	strcat(buf,"stdout\n");
	fputs(buf,stdout);
	printf("\nbuf:%s",buf);
}

void print_args(const char*fmt,...){
	va_list ap;
	/*get the start var arg address.*/
	va_start(ap,fmt);
	you_printf(fmt,ap);
	va_end(ap);
}
