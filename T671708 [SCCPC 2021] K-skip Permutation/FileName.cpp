#include<stdio.h>
int main(void) {
	int n, k;
	scanf_s("%d %d", &n, &k);
	int i,j;
	if (n <= k) {
		for (i = 1; i < n; i++) {
			printf("%d ", i);
		}
		printf("%d", n);
		return 0;
	}
	for (j = 1; j <= k-1; j++) {
		for (i = 0; i < n / k; i++) {
			printf("%d ", j + i*k);
		}
		if (j <= n % k) {
			printf("%d ", j + i * k);
		}
	}
		
	for (i = 0; i < (n / k)-1; i++) {
		printf("%d ", k + i * k);
	}
	printf("%d", k + k*(n / k - 1));
	return 0;
}
