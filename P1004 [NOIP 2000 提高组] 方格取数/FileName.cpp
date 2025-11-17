#include<stdio.h>
int f(int, int, int, int);
int max(int, int, int, int);
int arr[10][10];
int temp[10][10][10][10];
int main(void) {
	int n;
	scanf_s("%d", &n);
	int i, j,l,k;
	for (i = 1; i <= n; i++) for (j = 0; j <= n; j++)for (k = 0; k <= n; k++)for (l = 0; l <= n; l++) temp[i][j][l][k] = -1;

	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			arr[i][j] = 0;
		}
	}
	int a, b, c;
	while (scanf_s("%d %d %d", &a, &b, &c)) {
		if (a == 0 && b == 0 && c == 0) break;
		arr[a][b] = c;
	}
	printf("%d", f(n, n, n, n));
	return 0;

}
int f(int m, int n, int p, int q) {
	if (temp[m][n][p][q] != -1) return temp[m][n][p][q];
	if (m == 0 || n == 0 || p == 0 || q == 0) return 0;
	if (m != p || n != q) temp[m][n][p][q] = max(f(m - 1, n, p - 1, q), f(m, n - 1, p - 1, q), f(m - 1, n, p, q - 1), f(m, n - 1, p, q - 1)) + arr[m][n] + arr[p][q];
	else temp[m][n][p][q] = max(f(m - 1, n, p - 1, q), f(m, n - 1, p - 1, q), f(m - 1, n, p, q - 1), f(m, n - 1, p, q - 1)) + arr[m][n];
	return temp[m][n][p][q];
}
int max(int a, int b, int c, int d) {
	int t=a;
	if (t < b) t = b;
	if (t < c)t = c;
	if (t < d)t = d;
	return t;
}