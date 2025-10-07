#include<stdio.h>
int max(int arr[]);
int main(void) {
	int arr[10] = { 1, 2 ,3,4,5,6,7,8,9,10 };
	int i;
	i = max(arr);
	printf("%d", i);
	return 0;
}
int max(int arr[]) {
	int a,i;
	a = arr[0];
	for (i = 1; i < 10; i++) {
		if (arr[i] > a) {
			a = arr[i];
		}
	}
	return a;
}