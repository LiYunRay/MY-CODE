#include<stdio.h>
#include<math.h>
int arr[5005];
int max(int, int);
int min(int, int);
int main(void) {
	int l,n;
	scanf_s("%d", &l);
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++) scanf_s("%d", &arr[i]);
	int fin1, fin2;
	fin1 = fin2 = 0;
	for (int i = 0; i < n; i++) {
		fin1 = max(fin1, max(arr[i], l - arr[i] + 1));
	}
	for (int i = 0; i < n; i++) {
		fin2 = max(fin2, min(arr[i], l - arr[i] + 1));
	}

	printf("%d %d", fin2, fin1);
	return 0;
}
int max(int a, int b) {
	return a > b ? a : b;
}
int min(int a, int b) {
	return a > b ? b : a;
}