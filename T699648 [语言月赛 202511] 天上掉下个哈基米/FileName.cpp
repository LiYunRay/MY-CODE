#include<stdio.h>
int v[1005], l[1005];
int main(void) {
	int n, t;
	scanf_s("%d", &n);
	int i;
	for (i = 0; i < n; i++) scanf_s("%d %d", &v[i], &l[i]);
	scanf_s("%d", &t);
	int x, j,fin;
	for (i = 0; i < t; i++) {
		fin = 0;
		j = 0;
		scanf_s("%d", &x);
		while (x >= l[j]&&j<n) {
			x -= l[j];
			j += 1;
		}
		if (j == n) printf("%d\n", v[n - 1]);
		else if (x != 0)printf("%d\n", v[j]);
		else printf("%d\n", v[j - 1]);
	}
	return 0;
}