#include<stdio.h>
int main(void) {
	char name[20];
	printf("Please input your name.\n");
	scanf_s("%s", name, 20);
	printf("\"%s\"\n", name);
	printf("\"%20s\"\n",name);
	printf("\"%-20s\"\n",name);
	int a = sizeof(name);
	int b = a + 3;
	printf("\"   %s\"\n", name);
	return 0;
}