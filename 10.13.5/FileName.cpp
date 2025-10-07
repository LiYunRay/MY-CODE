#include<stdio.h>
double f(double arr[]);
int main(void) {
	double arr[5] = { 1,2,3,4,2 };
	double i=f(arr);
	printf("%lf", i);
	return 0;
}
double f(double arr[]) {
	double a, b, c;
	int i;
	a = b = arr[0];
	for (i = 0; i < 5; i++) {
		if (arr[i] > a) {
			a = arr[i];
		}
		if (arr[i] < b) {
			b = arr[i];
		}

	}
	c = a - b;
	return c;
}