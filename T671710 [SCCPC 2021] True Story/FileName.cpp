#include<stdio.h>
int arr[100000000];
int cla[100000];
int tim[100000];
int main(void) {
	int n, k, p0;
	double x;
	scanf_s("%d %d %lf %d", &n, &k, &x,&p0);
	int i;
	for (i = 0; i < n; i++) {
		scanf_s("%d", &arr[i]);
	}
	int rest = p0;
	double tm;
	int all = 0;
	for (i = 0; i < k; i++) {
		scanf_s("%d", &cla[i]);
	}
	for (i = 0; i < k; i++) {
		scanf_s("%d", &tim[i]);
	}
	for (i = 0; i < k; i++) {
		if (tim[i] - cla[i] > rest) {
			rest = tim[i] - cla[i];
		}
	}
	for (i = 0; i < n; i++) {
		tm = x / arr[i];
		if (tm <= rest) {
			all += 1;
		}
	}
	printf("%d", all);
	return 0;
}