#include<stdio.h>
int main(void) {
	int a;
	scanf_s("%f", &a);
	float b;
	b = a * 3.156e17;
	printf("%f", b);
	return 0;
}