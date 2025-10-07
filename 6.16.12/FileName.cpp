#include<stdio.h>
int main(void) {
	int i,n;
	float sum1, sum2;
	float a = 1;
	sum1 = 0;
	sum2 = 1;
	scanf_s("%d", &n);
	while (n > 0) {
		for (i = 1; i <= n; i++) {
			sum1 = sum1 + (1.0 /i);
		}
		for (i = 2; i <= n; i++) {
			a = a * (i - 1.0) / i * (-1.0);
			sum2 = sum2 + a;
		}
		printf("%f %f\n", sum1, sum2);
		scanf_s("%d", &n);
		sum1 = 0;
		sum2 = 1;
		a = 1;
	}
	return 0;
}