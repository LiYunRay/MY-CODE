#include<stdio.h>
int main(void) {
	float a, b, c;
	printf("please input megabite per second and the magabytes of the file\n");
	scanf_s("%f  %f", &a, &b);
	c = a*8 / b;
	printf("At %f megabits per second,a file of %f megabytes downloads in %f seconds", b, a, c);
	return 0;
}