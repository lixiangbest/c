/*************************************************************************
	> File Name: test.c
	> Description: 
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月16日 星期一 17时39分43秒
 ************************************************************************/
#include "unp.h"

#ifdef HAVE_MSGHDR_MSG_CONTROL
#define msg_control 1
#else
#define msg_control 0
#endif

int main(){
	printf("HAVE_MSGHDR_MSG_CONTROL:%d\n", msg_control);

	return 0;
}
