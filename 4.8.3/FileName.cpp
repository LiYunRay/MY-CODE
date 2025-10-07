#include<stdio.h>
int main(void) {
	float a;
	scanf_s("%f", &a);
	printf("The input is %f or %e", a, a);
	return 0;
}