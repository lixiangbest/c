/*
 * =====================================================================================
 *
 *       Filename:  define.c
 *
 *    Description:  define error.
 *
 *        Version:  1.0
 *        Created:  06/15/13 12:29:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Li Xiang (gk), lixiang-best@163.com
 *        Company:  Li Xiang in Xiamen China.
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<sys/socket.h>
#include<string.h>

#if defined(SCM_CREDS)	/*BSD interface*/
#define CREDSTRUCT cmsgcred
#define SCM_CREDTYPE SCM_CREDS
#elif defined(SCM_CREDENTIALS) /*Linux interface*/
#define CREDSTRUCT ucred
#define SCM_CREDTYPE SCM_CREDENTIALS
#else
#warning passing credentials is unsupported!
/*#error passing credentials is unsupported!*/
#endif

#define BLOCK 8192

#define MONCK(ARGTERM)\
	printf("The term "#ARGTERM" is a string\n");

#define errout(a,b,...)\
	fprintf(stderr, "File %s Line %d\n", a, b);\
	fprintf(stderr, __VA_ARGS__);

int main(void){
	perror("defined");
	
	printf("Macro:#BLOCK\n");
	
	MONCK("A TO B");

	errout(__FILE__, __LINE__, "Unexpected termination\n");

	int arr[3] = {1, 2, 3};
	printf("0x%x, 0x%x, 0x%x\n", &arr[0], arr, &arr);
	printf("%d, %d\n", (&arr[0])[0], arr[0]);
	
	char s[] = "ab-cd: ef;gh :i-jkl;mnop;qrs-tu: vwx-y;z";
	char *delim = "-: ";
	char *p;
	printf("\ns = %s| split = %s\n", s, delim);
	printf("split = %s\n\n", strtok(s, delim));
	while((p = strtok(NULL, delim)))
		printf("%s\n", p);

	return 0;
}
