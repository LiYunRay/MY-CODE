#include<stdio.h>
#include<string.h>
int main(void) {
	printf("please input your name\n");
	char name1[20], name2[20];
	scanf_s("%s %s", name1,20, name2,20);
	int a, b;
	a = strlen(name1);
	b = strlen(name2);
	printf("%-10s %-10s\n", name1, name2);
	printf("%-10d %-10d", a, b);
	return 0;
	
}