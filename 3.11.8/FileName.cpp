#include<stdio.h>
int main(void) {
	float a, b, c, d,e;
	scanf_s("%f",&a);
	b = 2*a;
	c = b / 8;
	d = c / 2;
	e = d / 3;
	printf("%f,%f,%f,%f", b, c, d, e);
	return 0;
}