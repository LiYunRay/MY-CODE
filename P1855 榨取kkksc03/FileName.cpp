#include<stdio.h>
int max(int, int);
int main(void) {
	int n, M, T;
	scanf_s("%d %d %d", &n, &M, &T);
	int i,j,m,t;
	int dp[201][201];
	int money[200], time[200];
	for (i = 0; i < n; i++) {
		scanf_s("%d %d", &money[i], &time[i]);
	}
	for (i = 0; i < 201; i++) {
		for (j = 0; j < 201; j++) {
			dp[i][j] = 0;
		}
	}
	for (i = 0; i < n; i++) {
		for (m = M; m >= money[i]; m--) {
			for (t = T; t >= time[i]; t--) {
				dp[m][t] = max(dp[m][t], dp[m - money[i]][t - time[i]] + 1);
			}
		}
	}
	printf("%d", dp[M][T]);
	return 0;

}
int max(int a, int b) {
	return a > b ? a : b;
}