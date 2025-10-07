#include<stdio.h>
int arr[10000];
int ind[10000];
int love[10000];
int main(void) {
	int T,q;
	int n, k, m;
	int i;
	scanf_s("%d", &T);
	for (q = 0; q < T; q++) {
		
		scanf_s("%d %d %d", &n, &k, &m);
		for (i = 0; i < n; i++) {
			scanf_s("%d", &arr[i]);
			love[i] = 0;
		}
		for (i = 0; i < k; i++) {
			ind[i] = 0;
		}
		if (m >= 2 * n) {
			for (i = 0; i < 2 * n; i++) {
				if (ind[arr[i % n]-1] == 0) {
					ind[arr[i % n]-1] += 1;
				}
				else {
					ind[arr[i % n]-1] -= 1;
					love[i % n] += 1;
				}
			}
			for (i = 0; i < n; i++) {
				love[i] *= m / (2 * n);
			}
			for (i = 0; i < m % (2 * n); i++) {
				if (ind[arr[i % n]-1] == 0) {
					ind[arr[i % n]-1] += 1;
				}
				else {
					ind[arr[i % n]-1] -= 1;
					love[i % n] += 1;
				}
			}
		}
		else {
			for (i = 0; i < m ; i++) {
				if (ind[arr[i % n]-1] == 0) {
					ind[arr[i % n]-1] += 1;
				}
				else {
					ind[arr[i % n]-1] -= 1;
					love[i % n] += 1;
				}
			}
		}
		for (i = 0; i < n; i++) {
			printf("%d ", love[i]);
		}
		printf("\n");
	}
	return 0;
}
