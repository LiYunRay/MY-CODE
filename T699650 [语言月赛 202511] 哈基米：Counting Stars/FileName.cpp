#include<stdio.h>
int a[1005], b[1005], c[1005];
int fin[400][400];
int max(int, int);
int min(int, int);
int main(void) {
	int n,i;
	int t = 0;
	scanf_s("%d", &n);
	for (i = 0; i < n; i++) scanf_s("%d %d %d", &a[i], &b[i], &c[i]);
	int j;
	for (i = 0; i < 400; i++) for (j = 0; j < 400; j++) fin[i][j] = 0;
	for (i = 0; i < n; i++) {
		if (fin[b[i]][c[i]] != 0) fin[b[i]][c[i]] = min(fin[b[i]][c[i]], a[i]);
		else fin[b[i]][c[i]] = a[i];
	}
	for (i = 0; i < 400; i++)for (j = 0; j < 400; j++) t = max(t, fin[i][j]);
	printf("%d", t);
	return 0;
}
int max(int a, int b) {
	return a > b ? a : b;

}
int min(int a, int b) {
	return a > b ? b : a;

}