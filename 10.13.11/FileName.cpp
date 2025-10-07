#include<stdio.h>
void t(int [][5]);
void p(int [][5]);
int main(void) {
	int arr[3][5];
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 5; j++) {
			arr[i][j] = i+j;
		}
	}
	p(arr);
	printf("\n");
	t(arr);
	p(arr);
	return 0;
}
void t(int arr[][5]) {
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 5; j++) {
			arr[i][j] = arr[i][j]*2;
		}
	}
}
void p(int arr[][5]) {
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 5; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}