/*
 * =====================================================================================
 *
 *       Filename:  defs.h
 *
 *    Description:  test makefile defines
 *
 *        Version:  1.0
 *        Created:  10/23/12 20:17:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#ifndef mfile
#define mfile
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdarg.h>
#define Maxline 80

/*fun apply*/
/*print var arguments*/
void you_printf(const char*fmt,va_list ap);
void print_args(const char*fmt,...);
#endif

