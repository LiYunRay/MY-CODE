#include<stdio.h>
double f(double, int);
int main(void) {
	double a, c;
	int b;
	scanf_s("%lf %d", &a, &b);
	c = f(a, b);
	printf("%lf", c);
}
double f(double a, int b) {
	double fin;
	if (a == 0) {
		fin = 0;
	}
	else {
		if (b == 0) {
			fin = 1;
		}
		else if (b > 1) {
			fin = f(a, b - 1) * a;
		}
		else if (b = 1) {
			fin = a;
		}
		else {
			fin = 1.0 / f(a, -b);
		}
	}
	return fin;
}
