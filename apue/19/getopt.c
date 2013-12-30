/*
 * =====================================================================================
 *
 *       Filename:  getopt.c
 *
 *    Description:  getopt function usage.
 *
 *        Version:  1.0
 *        Created:  06/26/13 23:23:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"

int main(int argc, char *argv[]){
	/*int aflag = 0, bflag = 0, cflag = 0;*/
	int ch;
	printf("optind:%d, opterr: %d\n", optind, opterr);
	printf("--------------------\n");
	while((ch = getopt(argc, argv, "ab:c:de::")) != -1){
		printf("optind:%d,argc:%d,argv[%d]:%s\n", optind, argc, optind,argv[optind]);
		switch(ch){
			case 'a':
				printf("HAVE option: -a\n\n");
				break;
			case 'b':
				printf("HAVE option: -b\n");
				printf("The argument of -b is %s\n\n", optarg);
				break;
			case 'c':
				printf("HAVE option: -c\n");
				printf("The argument of -c is %s\n\n", optarg);
				break;
			case 'd':
				printf("HAVE option: -d\n");
				break;
			case 'e':
				printf("HAVE option: -e\n");
				printf("The argument of -c is %s\n\n", optarg);
				break;
			case '?':
				printf("Unknow option: %c\n", (char)optopt);
		}
	}
	printf("----------------\n");
	printf("optind=%d,argv[%d]=%s\n", optind,optind,argv[optind]);

	printf("-----------------\n");
	
	for(ch=0; ch< argc; ch++){
		printf("ch=%d, optind=%d, argv=%s, argv=%s\n", ch, optind, argv[ch], argv[optind]);
		if(ch==optind) optind++;
	}

	return 0;
}

