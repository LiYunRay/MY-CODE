#include<stdio.h>
void f(int[], int[],int[]);
int main(void) {
	int arr[4] = { 2,4,6,8 };
	int num[4] = { 1,3,5,7 };
	int fin[4];
	f(arr, num, fin);
	int i;
	for (i = 0; i < 4; i++) {
		printf("%d\n", fin[i]);
	}
	return 0;
}
void f(int arr[], int num[], int fin[]) {
	int i;
	for (i = 0; i < 4; i++) {
		fin[i] = arr[i] + num[i];
	}
}