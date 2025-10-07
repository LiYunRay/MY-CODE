#include<stdio.h>
int main(void) {
	int arr[10];
	int tall;
	int i;
	int fin = 0;
	for (i = 0; i < 10; i++) {
		scanf_s("%d", &arr[i]);
	}
	scanf_s("%d", &tall);
	for (i = 0; i < 10; i++) {
		if (arr[i] <= (tall + 30)) {
			fin += 1;
		}
	}
	printf("%d", fin);
	return 0;
}