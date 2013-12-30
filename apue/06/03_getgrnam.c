/*
 * =====================================================================================
 *
 *       Filename:  01_getpwnam.c
 *
 *    Description:  get pwd name
 *
 *        Version:  1.0
 *        Created:  05/01/13 10:52:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<grp.h>
#include<stddef.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

struct group * mygetgpnam(const char *name){
	struct group *gp;
	setgrent();
	while((gp=getgrent()) != NULL)
		if(strcmp(name, gp->gr_name) == 0)
			break;/*found a match*/
	endgrent();
	return(gp);
}

int main(int argc, char *argv[]){
	struct group *gp;
	char **gmem;
	int i,j=0;
	if(argc<2){
		printf("argc must be greater than 2!");
		return 0;
	}
	
	for(i=1;i<argc;i++){
		if((gp=mygetgpnam(argv[i]))!=NULL){
			printf("---------------------------------\n");
			printf("group name: %s\n", gp->gr_name);
			printf("pwd: %s\n", gp->gr_passwd);
			printf("gid: %d\n", gp->gr_gid);
			gmem = gp->gr_mem;/*group member*/
			while(*gmem != NULL){
				/*printf("\tgroup mem:%s\n",gp->gr_mem[j++]);*/
				printf("\tgroup mem:%s\n",*gmem);
				gmem++;
			}
			printf("---------------------------------\n");
		}else{
			printf("%s not found!\n",argv[i]);
			perror(argv[i]);
		}
	}
	return 0;
}

