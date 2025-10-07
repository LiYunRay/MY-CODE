#include<stdio.h>
void f(int[][21], int);
int main(void) {
	int n,fin;
	fin = 0;
	int i,j;
	scanf_s("%d", &n);
	int arr[21][21];
	for (i = 0; i < 21; i++) {
		for (j = 0; j < 21; j++) {
			arr[i][j] = 0;
		}
	}
	arr[1][0] = 1;
	for (i = 1; i < n; i++) {
		f(arr, i);
	}
	for (j = 0; j < 21; j++) {
		fin += arr[n][j];
	}
	printf("%d", fin);
	return 0;
}
void f(int arr[][21], int a) {
	int i, j;
	for (i = 0; i < 21; i++) {
		for (j = 0; j <= i + 1; j++) {
			arr[a + 1][j] += arr[a][i];
		}
	}
}