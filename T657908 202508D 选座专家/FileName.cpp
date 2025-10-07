#include<stdio.h>
int main(void) {
	int n;
	int arr[100];
	int i, j,k;
	int all;
	scanf_s("%d", &all);
	for(k=0;k<all;k++) {
		scanf_s("%d", &n);
		for (i = 0; i < n; i++) {
			scanf_s("%d", &arr[i]);
		}
		int fin = 0;
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= arr[i - 1]; j++) {
				if (i == 1) {
					fin += 1;
				}
				else if (j == 1) {
					fin += 1;
				}
				else if (j == arr[i - 1]) {
					fin += 1;
				}
				else if (((i * j) % 10) == 6) {
					fin += 1;
				}
			}
		}
		printf("%d\n", fin);
		fin = 0;
	}
	return 0;

}