#include<stdio.h>
long long arr[1000], brr[1000], crr[1000], rank[1000];
long long max(long long, long long);
void f(int,int);
int len(int[]);
int fin[1000];
int temp[1000];
void ex(int,int);
int main(void) {
	int n;
	scanf_s("%d", &n);
	int i,j,x,y;
	scanf_s("%d %d", &x, &y);
	for (i = 0; i < n; i++) scanf_s("%lld %lld", &arr[i], &brr[i]);
	for (i = 0; i < n; i++) {
		crr[i] = (arr[i] - 1) * brr[i];
		rank[i] = i;
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (crr[rank[j]] > crr[rank[j + 1]]) ex(j, j + 1);
		}
	}
	for (i = 0; i < 1000; i++) fin[i] = 0;
	for (i = 0; i < 1000; i++) temp[i] = 0;
	fin[0] = 1;
	

	printf("%lld", fin);
	return 0;
}
void ex(int i, int j) {
	int temp;
	temp = rank[i];
	rank[i] = rank[j];
	rank[j] = temp;
}
long long max(long long a, long long b) {
	return a > b ? a : b;
}
int len(int arr[1000]) {
	int i;
	for (i = 999; i >= 0; i--) {
		if (arr[i] != 0) break;
	}
	return i;
}
void f(int a, int b) {

}