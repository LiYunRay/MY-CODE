#include<stdio.h>
int arr[100005];
int main(void) {
	int n;
	scanf_s("%d", &n);
	int i;
	for (i = 0; i < n; i++) scanf_s("%d",&arr[i]);
	int fin = 0;
	for (i = 0; i < n - 1; i++) {
		if (arr[i] % 2 != arr[i + 1] %2) {
			fin += 1;
		}
	}
	printf("%d", fin);
	return 0;

}