/*************************************************************************
	> File Name: param.c
	> Description: parameter.
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月28日 星期六 05时19分46秒
 ************************************************************************/
#include "unp.h"

/*print function arguments.*/
struct char_print_parms{
	/*use to print char*/
	char character;
	/*print times*/
	int count;
};

/*print data to stderr*/
void *char_print(void *parameters){
	/*change function point to right type.*/
	struct char_print_parms *p = (struct char_print_parms *)parameters;
	int i;
	for(i=0; i < p->count; i++){
		fputc(p->character, stderr);
	}
	return NULL;
}

int main(){
	pthread_t thread1_id;
	pthread_t thread2_id;
	struct char_print_parms thread1_args;
	struct char_print_parms thread2_args;

	/*create thread to print x.*/
	thread1_args.character = 'x';
	thread1_args.count = 3000;
	pthread_create(&thread1_id, NULL, &char_print, &thread1_args);

	/*create thread to print x.*/
	thread2_args.character = 'o';
	thread2_args.count = 2000;
	pthread_create(&thread2_id, NULL, &char_print, &thread2_args);

	/*wait for the end of thread1*/
	pthread_join(thread1_id, NULL);
	/*wait for the end of thread2*/
	pthread_join(thread2_id, NULL);

	return 0;
}


