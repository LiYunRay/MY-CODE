#include<stdio.h>
double max(double, double);
int main(void) {
	double a, b,c;
	scanf_s("%lf %lf", &a, &b);
	c = max(a, b);
	printf("%lf", c);
	return 0;

}
double max(double a, double b) {
	if (a >=b) {
		return a;
	}
	else {

		return b;
	}
}