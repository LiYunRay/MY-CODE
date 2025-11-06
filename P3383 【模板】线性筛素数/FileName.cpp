#include<stdio.h>
#include<stdlib.h>
int prime[1000000];
int main(void) {
	int n, q;
	scanf_s("%d %d", &n,&q);

	int i, j;
	int* arr = (int*)malloc((n+1) * sizeof(int));
	int* inquire = (int*)malloc(q * sizeof(int));
	for (i = 0; i < q; i++) scanf_s("%d", &inquire[i]);
	for (i = 1; i <= n; i++) arr[i] = 0;
	int num = 0;
	for (i = 2; i <= n; i++) {
		if (arr[i] == 0) {
			prime[num] = i;
			num += 1;
		}
		for (j = 2; j <= i; j++) {
			if(arr[j]==0&&(i*j)<=n) arr[i * j] = 1;
			if (i % j == 0) break;
		}
	}
	for (i = 0; i < q; i++) printf("%d\n", prime[inquire[i] - 1]);
}