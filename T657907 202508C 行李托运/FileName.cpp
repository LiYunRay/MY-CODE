#include<stdio.h>
int main(void) {
	int n;
	int arr[10000];
	int i;
	scanf_s("%d", &n);
	for (i = 0; i < n; i++) {
		scanf_s("%d", &arr[i]);
	}
	int k=0,p=0;
	for (i = 0; i < n; i++) {
		if (arr[i] == -1) {
			k += 1;
		}
		else if (arr[i] == 1) {
			break;
		}
		else {
			k += 1;
			p += 1;
		}
	}
	printf("%d %d", k,p);
	return 0;
}