#include<stdio.h>
int main(void) {
	long a, b;
	scanf_s("%ld", &a);
	scanf_s("%ld", &b);
	long c = a + b;
	printf("%ld", c);
	return 0;
}