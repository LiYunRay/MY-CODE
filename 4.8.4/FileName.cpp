#include<stdio.h>
int main(void) {
	float a;
	char name[20];
	printf("Please input your name and length\n");
	scanf_s("%s %f", name, 20,&a);
	a = a / 100;
	printf("%s,you are %f meters tall.", name, a);
	return 0;

}