#include<stdio.h>
int main(void) {
	char name1[20], name2[20];
	printf("Please input your name.\n");
	scanf_s("%s %s", name1,20,name2,20);
	printf("%s,%s", name1, name2);
	return 0;

}