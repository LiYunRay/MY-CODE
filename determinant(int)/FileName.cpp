#include<stdlib.h>
#include<stdio.h>
void f(int, long long**);
int main(void) {
	int n;
	scanf_s("%d", &n);
	long long** a = (long long**)malloc(n * sizeof(long long*));
	int i, j, k;
	for (i = 0; i < n; i++) {
		a[i] = (long long*)malloc(n * sizeof(long long));
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			scanf_s("%lld", &a[i][j]);
		}
	}
	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			for (k = i + 1; k < n; k++) {
				a[j][k] -= a[i][k] * a[j][i];
			}
			a[j][i] = 0;
		}
	}
	long long fin = a[n - 1][n - 1];
	printf("%d", fin);
	for (i = 0; i < n; i++) {
		free(a[i]);
	}
	free(a);
	return 0;

}