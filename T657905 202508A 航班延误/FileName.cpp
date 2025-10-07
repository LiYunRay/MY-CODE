#include<stdio.h>
int main(void) {
	int  a, b, t;
	double x;
 	scanf_s("%lf %d %d %d", &x, &a, &b, &t);
	x = x / 60;
	if (x <= 1) {
		printf("0");

	}
	else if (x >= 1&& x < 2) {
		printf("%d", a);
	}
	else if (x >= 2 && x < 4) {
		printf("%d", b);
	}
	else {
		printf("%d", t);
	}
}