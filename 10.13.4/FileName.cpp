#include<stdio.h>
int max(double arr[]);
int main(void) {
	double arr[10] = { 1, 2 ,3,4,5,6,7,8,9,10 };
	int i;
	i = max(arr);
	printf("%d", i);
	return 0;
}
int max(double arr[]) {
	int  i,j;
	j = 0;
	double a=arr[0];
	for (i = 1; i < 10; i++) {
		if (arr[i] > a) {
			a = arr[i];
			j = i;
		}
	}
	return j;
}