/*
 * =====================================================================================
 *
 *       Filename:  02_reenter.c
 *
 *    Description:  my reenter.
 *
 *        Version:  1.0
 *        Created:  05/14/13 05:02:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include "apue.h"
#include<pwd.h>

static void my_alarm(int signo){
	struct passwd *rootptr;
	printf("in signal handler\n");
	/*getpwnam need not be reentrant*/
	if((rootptr = getpwnam("root")) == NULL){
		err_sys("getpwnam(root) error");
	}
	alarm(1);
}

int main(void){
	struct passwd *ptr;
	signal(SIGALRM, my_alarm);
	alarm(1);/*send a singal every second.call the signal handler.*/
	for(;;){
		if((ptr=getpwnam("suncco"))==NULL)
			err_sys("getpwnam error");
		/*current get name is not equal to suncco, then print it*/
		if(strcmp(ptr->pw_name, "suncco") != 0)
			printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
	}
}

