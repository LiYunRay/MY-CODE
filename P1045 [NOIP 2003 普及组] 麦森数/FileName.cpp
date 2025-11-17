#include<stdio.h>
char arr[1000000];
int main(void) {
	int i,j;
	int n;
	scanf_s("%d", &n);
	for (i = 0; i < 1000000; i++) arr[i] = 0;
	arr[0] = 1;
	int len = 1;
	for (j = 0; j < n; j++) {
		for (i = 0; i < len; i++) {
			arr[i] *= 2;
		}
		for (i = 0; i < len; i++) if (arr[i] >= 10) {
			arr[i + 1] += arr[i] / 10;
			arr[i] %= 10;
		}
		if (arr[len] != 0) len += 1;
	}
	printf("%d\n", len);
	arr[0] -= 1;
	for (i = 499; i >= 0; i--) {
		printf("%d", arr[i]);
		if (i % 100 == 0) printf("\n");
	}
	return 0;
}