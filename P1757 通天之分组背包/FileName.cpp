#include<stdio.h>
int a[1000], b[1000], c[1000];
int n, m;
long long max(long long, long long);
int main(void) {
	scanf_s("%d %d", &m, &n);
	int i,j,k;
	long long dp[1000];
	for (i = 0; i < 1000; i++) {
		dp[i] = 0;
	}
	for (i = 0; i < n; i++) {
		a[i] = b[i] = c[i] = 0;
	}
	for (i = 0; i < n; i++) {
		scanf_s("%d %d %d", &a[i], &b[i], &c[i]);

	}

	int pack=c[0];
	for (i = 1;i<100; i++) {
		pack = pack > c[i] ? pack : c[i];
	}
	
	for (i = 1; i <=pack; i++) {
		for (j = m - 1; j >= 0; j--) {
			for (k = 0; k < n; k++) {
				if (c[k] == i) {
					if (j >= a[k])
						dp[j] = max(dp[j], dp[j - a[k]] + b[k]);
					else if (j == a[k] - 1)
						dp[j] = max(dp[j], b[k]);
					else
						continue;
				}
				else
					continue;

			}
		}
	}
	printf("%lld", dp[m - 1]);
	return 0;
}
long long max(long long a, long long b) {
	return a > b ? a : b;
}