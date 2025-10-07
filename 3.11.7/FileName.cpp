#include<stdio.h>
int main(void) {
	float a;
	scanf_s("%f", &a);
	a = a * 2.54;
	printf("%f", a);
	return 0;
}