#include<stdio.h>
int main(void) {
	float a;
	scanf_s("%f", &a);
	float b;
	int c;
	c = 10 * a;
	
	int d;
	d = c/1000 + (c / 100) % 10 * 10 + (c / 10) % 10 * 100 + c % 10 * 1000;
	b = d / 1000.0;
	printf("%.3f", b);
	return 0;
}