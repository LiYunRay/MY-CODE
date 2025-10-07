#include<stdio.h>
double cube(double);
int main(void) {
	double a, b;
	scanf_s("%lf", &a);
	b = cube(a);
	printf("%lf", b);
	return 0;

}
double  cube(double x) {
	return x * x * x;
}



