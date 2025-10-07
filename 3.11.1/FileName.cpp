#include<stdio.h>
int main() {
	float a;
	a = 1.0;
	a = a + 1000000000000000000;
	float b;
	b = 2e-3;
	b = b / 10000;
	int c;
	c = 1;
	c = c + 1000000000000000;
	printf("%f,%f,%d", a, b,c);
	return 0;
}