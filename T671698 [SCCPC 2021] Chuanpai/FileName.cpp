#include<stdio.h>
int main(void) {
	int T, q;
	int n, i;
	int sum;
	scanf_s("%d", &T);
	for (q = 0; q < T; q++) {
		sum = 0;
		scanf_s("%d", &n);
		for (i = 1; i <= 6&&i<=n/2; i++) {
			if (n - i >= 1 && n - i <= 6) {
				sum += 1;
			}
		}
		printf("%d\n", sum);
	}
	return 0;
}