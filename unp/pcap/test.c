/*************************************************************************
	> File Name: test.c
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月27日 星期五 20时38分56秒
 ************************************************************************/
#include<stdio.h>

union big{
	char a;
	int b;
};

struct s{
	char a;
	int b;
	short c;
	char d;
};

struct dm{
	int a;
	double b;//gcc pack is 4 bytes, that is special.the pack is 8 bytes in common.
	double c;
	char d;
};

int main(){
	union big m;
	m.b = 1;
	printf("m.b = %d,sizeof union = %d,sizeof struct = %d\n", m.a==1, sizeof m, sizeof(struct s));
	printf("struct = %d\n", sizeof(struct dm));
	
	m.a = 0x1;
	printf("m.b = %x\n", m.b);

	int a = 0x1234;
	char b = *(char *)&a;
	printf("b = %d\n", b == 0x34);

	printf("EOF = %d\n", EOF);
}
