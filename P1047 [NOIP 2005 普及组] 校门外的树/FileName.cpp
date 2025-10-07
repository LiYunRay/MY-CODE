#include<stdio.h>
int main(void) {
	int l, m;
	int a, b;
	int arr[10000];
	scanf_s("%d %d", &l, &m);
	int i,j;
	int fin=0;
	for (i = 0; i <= l; i++) {
		arr[i] = 1;
	}
	for (i = 0; i < m; i++) {
		scanf_s("%d %d", &a, &b);
		for (j = a; j <= b; j++) {
			arr[j] = 0;
		}
		
	}
	for (i = 0; i <= l; i++) {
		if (arr[i] == 1) {
			fin += 1;
		}

	}
	printf("%d", fin);
	return 0;
}