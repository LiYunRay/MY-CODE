#include<stdio.h>
int fin[305];
void mul(int);
int main(void) {
	int n;
	scanf_s("%d", &n);
	int i;
	int num=0;
	int arr[200];
	for (i = 0; i < 300; i++) fin[i] = 0;
	fin[0] = 1;
	for (i = 0; i < 199; i++) arr[i] = 0;
	for (i = 2; i <= n; i++) {
		num += i;
		arr[i] = 1;
		if (num >= n) break;
	}
	int t = num - n;
	if (t == 1) {
		arr[2] = 0;
		arr[i] = 0;
		arr[i + 1] = 1;
	}
	else  arr[t] = 0;
	for (i = 0; i < 200; i++) if (arr[i] == 1) mul(i);
	
	int len;
	for (i = 299; i >= 0; i--) if (fin[i] != 0) break;
	len = i;
	for (i = 0; i < 199; i++) if (arr[i] == 1) printf("%d ", i);
	printf("\n");
	for (i = len; i >= 0; i--) {
		printf("%d", fin[i]);
	}
}
void mul(int a) {
	int i;
	for (i = 0; i < 300; i++) fin[i] *= a;
	for (i = 0; i < 300; i++) {
		if (fin[i] >= 10) {
			fin[i + 1] += fin[i] / 10;
			fin[i] %= 10;
		}
	}



}