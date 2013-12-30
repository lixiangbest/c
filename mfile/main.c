/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  main function for c
 *
 *        Version:  1.0
 *        Created:  10/23/12 20:50:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include"defs.h"
#include"funs.h"

int main(int argc, char *argv[]){
	const char*fmt = "error,permission denied!";
	print_args(fmt, "%d", 3);
	printf("\nmax=%d",max(5, 7));
	printf("\nEXIT_SUCCESS=%d", EXIT_SUCCESS);
	return EXIT_SUCCESS;
}
/* ----------  end of function main  ---------- */

