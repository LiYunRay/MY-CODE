#include<stdio.h>
#include <stdlib.h>
int f(int, int);
int main(void) {
	int fin=0;
	int n;
	int i, j;
	int a[10000], b[10000], c[10000];
	scanf_s("%d", &n);
	for (i = 0; i < n; i++) {
		scanf_s("%d", &a[i]);
	}
	for (i = 0; i < n; i++) {
		scanf_s("%d", &b[i]);
	}
	for (i = 0; i < n; i++) {
		scanf_s("%d", &c[i]);
	}
	for (i = 0; i < n; i++) {
		fin += f(0, (c[i] - abs(a[i] - b[i])));

	}
	printf("%d", fin);
	return 0;
}
int f(int a, int b) {
	if (a >= b) {
		return a;
	}
	else {
		return b;
	}
}