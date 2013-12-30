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
#include<pwd.h>
#include<stddef.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

struct passwd * mygetpwnam(const char *name){
	struct passwd *ptr;
	/*setpwent();*/
	while((ptr=getpwent()) != NULL)
		if(strcmp(name, ptr->pw_name) == 0)
			break;/*found a match*/
	endpwent();
	return(ptr);
}

int main(int argc, char *argv[]){
	struct passwd *ptr;
	int i;
	if(argc<2){
		printf("argc must be greater than 2!");
		return 0;
	}
	printf("current user name :\t\t %s\n", getpwuid(getuid())->pw_name);
	printf("current user id :\t\t %d\n", getuid());
	printf("current group id :\t\t %d\n", getgid());
	printf("current effective user id :\t\t %d\n", geteuid());
	printf("current effective group id :\t\t %d\n", getegid());
	
	for(i=1;i<argc;i++){
		if((ptr=mygetpwnam(argv[i]))!=NULL){
			printf("---------------------------------\n");
			printf("user: %s\n", ptr->pw_name);
			printf("pwd: %s\n", ptr->pw_passwd);
			printf("uid: %d\n", ptr->pw_uid);
			printf("gid: %d\n", ptr->pw_gid);
			printf("uifo: %s\n", ptr->pw_gecos);
			printf("home: %s\n", ptr->pw_dir);
			printf("shell: %s\n", ptr->pw_shell);
			printf("---------------------------------\n");
		}else{
			printf("%s not found!\n",argv[i]);
			perror(argv[i]);
		}
	}
	return 0;
}

