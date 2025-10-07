#include<stdio.h>
void rank(double* a,double* b, double* c);
double max(double, double);
int main(void) {
	double a, b, c;
	scanf_s("%lf %lf %lf", &a, &b, &c);
	rank(&a, &b, &c);
	printf("%lf %lf %lf", a, b, c);
	return 0;
}
void rank(double* a, double* b, double* c) {
	double i, j, k;
	i = max(*a, max(*b, *c));
	if (i == *a) {
		j = max(*b, *c);
		if (j == *b) {
			k = *c;
		}
		else {
			k = *b;
		}
	}
	if (i == *b) {
		j = max(*a, *c);
		if (j == *a) {
			k = *c;
		}
		else {
			k = *a;
		}
	}
	if (i == *c) {
		j = max(*b, *a);
		if (j == *b) {
			k = *a;
		}
		else {
			k = *b;
		}
	}
	*a = i;
	*b = j;
	*c = k;
}
double max(double a, double b) {
	if (a >= b) {
		return a;
	}
	else {
		return b;
	}
}