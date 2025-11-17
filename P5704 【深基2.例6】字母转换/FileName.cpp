#include<stdio.h>
#include<ctype.h>
int main(void) {
	char a, b;
	scanf_s("%c", &a);
	b = toupper(a);
	printf("%c", b);
	return 0;


}