#include<stdio.h>
#include<string.h>
int main(void) {
	char name[40];
	printf("hello\n");
	scanf_s("%s",name,40);
	printf("%s\n", name);
	int a, b;
	a = sizeof(name);
	b = strlen(name);
	printf("%d,%d", a, b);
	return 0;
}