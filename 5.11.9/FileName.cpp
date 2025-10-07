#include<stdio.h>
void tem(double);
int main(void) {
	double a;
	scanf_s("%lf",&a);
	tem(a);
	return 0;
}

void tem(double x) {
	double m, n;
	m = 5.0 / 9.0 * (x - 32);
	n = m + 273.16;
	printf("%lf,%lf", m, n);
}
