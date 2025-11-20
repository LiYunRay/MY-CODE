#include<stdio.h>
#include<stdlib.h>
int main(void) {
	int n, d, t, c;
	int* arr;
	scanf_s("%d %d", &n, &d);
	arr = (int*)malloc(n * sizeof(int));
	int i;
	int num = 0;
	for (i = 0; i < n; i++) scanf_s("%d", &arr[i]);
	for (i = 1; i < n; i++) {
		if (arr[i] <= arr[i - 1]) {
			c = arr[i - 1] - arr[i];
			t = c / d + 1;
			num += t;
			arr[i] += t * d;
		}
	}
	printf("%d", num);
	return 0;
}