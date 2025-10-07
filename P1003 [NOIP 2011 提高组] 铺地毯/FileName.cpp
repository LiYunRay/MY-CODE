#include<stdio.h>
int main(void) {
	int n;
	scanf_s("%d", &n);
	int arr[10000][4];
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < 4; j++) {
			scanf_s("%d", &arr[i][j]);
		}
	}
	int a, b;
	scanf_s("%d", &a);
	scanf_s("%d", &b);
	j = 0;
	for (i = n - 1; i >= 0; i--) {
		if (a >= arr[i][0] && a < (arr[i][0] + arr[i][2]) && b >= arr[i][1] && b < (arr[i][1]+arr[i][3])) {
			printf("%d", i + 1);
			break;
		}
		j += 1;
	}
	if (j == n) {
		printf("-1");
	}
	return 0;
}