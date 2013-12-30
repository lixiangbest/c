/*
 * =====================================================================================
 *
 *       Filename:  02_getspnam.c
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
#include<shadow.h>
#include<stddef.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

struct spwd * mygetspnam(const char *name){
	struct spwd *sp;
	setspent();
	while((sp=getspent()) != NULL)
		if(strcmp(name, sp->sp_namp) == 0)
			break;/*found a match*/
	endspent();
	return(sp);
}

int main(int argc, char *argv[]){
	struct spwd *sp;
	int i;
	if(argc<2){
		printf("argc must be greater than 2!");
		return 0;
	}
	
	for(i=1;i<argc;i++){
		if((sp=mygetspnam(argv[i]))!=NULL){
			printf("---------------------------------\n");
			printf("login name: %s\n", sp->sp_namp);
			printf("encrypted passwd: %s\n", sp->sp_pwdp);
			printf("date of last change: %ld\n", sp->sp_lstchg);
			printf("min number of days between changes: %ld\n", sp->sp_min);
			printf("max number of days between changes: %ld\n", sp->sp_max);
			printf("number of days of warning: %ld\n", sp->sp_warn);
			printf("number of days after passwd: %ld\n", sp->sp_inact);
			printf("days since 1/1/1970 until account expires: %ld\n", sp->sp_expire);
			printf("reserved for future use: %ld\n", sp->sp_flag);
			printf("---------------------------------\n");
		}else{
			printf("%s not found!\n",argv[i]);
			perror(argv[i]);
		}
	}
	return 0;
}

