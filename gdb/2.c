#include<stdio.h>
#include<stdlib.h>
typedef struct{
	int i;
	char *s;
}student;

typedef union{
	int i;
	char c;
}ts;

main(){
	student stu;
	ts ut;
	int len = 5;
	int *array = (int*)malloc(len*sizeof(int));
	int i;
	for(i=0;i<len;i++){
		array[i] = i;
		printf("arr[%d]=%d\n",i,array[i]);
	}
	// struct start
	stu.i = 10;
	stu.s = "lixiang";
	printf("i=%d,name=%s\n",stu.i,stu.s);
	// union
	ut.c = 'A';
	printf("ut.c = %d",ut.c);
	return 0;
}
