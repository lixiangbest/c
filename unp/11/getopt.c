/*
 * =====================================================================================
 *
 *       Filename:  getopt.c
 *
 *    Description:  getopt function usage.
 *
 *        Version:  1.0
 *        Created:  11/23/13 20:45:55
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
#include<unistd.h>

int main(int argc, char **argv){
	int result;
	//opterr = 0;//forbit stderr info print.
	while( (result = getopt(argc, argv, "ab:c::")) != -1){
		switch(result){
			case 'a':
				printf("option=a, optopt=%c, optarg=%s\n", optopt, optarg);
				break;
			case 'b':
				printf("option=b, optopt=%c, optarg=%s\n", optopt, optarg);
				break;
			case 'c':
				printf("option=c, optopt=%c, optarg=%s\n", optopt, optarg);
				break;
			case '?':
				printf("result=?, optopt=%c, optarg=%s\n", optopt, optarg);
				break;
			default:
				printf("default, result=%c\n", result);
		}
		printf("argv[%d]=%s\n", optind, argv[optind]);
	}
	printf("result=-1, optind=%d\n", optind);//set the last optind position

	for(result=optind;result<argc;result++)
		printf("-------argv[%d]=%s\n", result, argv[result]);

	//set the last command parameter, see the order.
	for(result=1;result < argc;result++)
		printf("\nat the end------argv[%d]=%s\n", result, argv[result]);
	return 0;
}

