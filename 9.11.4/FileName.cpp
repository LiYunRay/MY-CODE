#include<stdio.h>
double H(double, double);
int main(void) {
	double a, b,c;
	scanf_s("%lf %lf", &a, &b);
	c = H(a, b);
	printf("%lf", c);
	return 0;
}
double H(double a, double b) {
	double c;
	c = 2 / (1 / a + 1 / b);
	return c;
}