#include<stdio.h>
int f(int, int);
int num[100][10000];
int arr[100];
int main(void) {
	int n, m;
	scanf_s("%d %d", &n, &m);
	int i, j;
	for (i = 0; i < n; i++) {
		scanf_s("%d", &arr[i]);
	}
	for (i = 0; i < 100; i++) {
		for (j = 0; j < 10000; j++) {
			num[i][j] = -1;
		}
	}
	int fin=f(n, m);
	printf("%d", fin);
	return 0;

}
int f(int n, int m) {




	if (m == 0) {
		return 1;
	}
	else if (n == 0) {
		return 0;
	}
	else if (m < 0) {
		return 0 ;
	}
	else {
		if (num[n - 1][m - 1] != -1) {
			return num[n - 1][m - 1];
		}

		else {
				num[n - 1][m - 1] = f(n - 1, m) + f(n - 1, m - arr[n - 1]);
				return(num[n-1][m-1]);
			

		}
	}
}
