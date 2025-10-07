#include<stdio.h>
void largeof(double *a,double *b);
int main(void) {
	double a, b;
	scanf_s("%lf %lf", &a, &b);
	largeof(&a, &b);
	printf("%lf %lf", a, b);
	return 0;
}
void largeof(double* a, double* b) {
	if (*a >= *b) {
		*b = *a;
	}
	else {
		*a = *b;
	}
}