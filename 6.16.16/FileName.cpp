#include<stdio.h>
int main(void) {
	float a, b;
	a = b = 100;
	int i = 0;
	while (a >= b) {
		a = a + 10;
		b = b * 1.05;
		i += 1;
	}
	printf("%d,%f,%f", i, a, b);
	return 0;
}