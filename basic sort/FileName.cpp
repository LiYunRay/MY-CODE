#include<stdio.h>
void f(double[]);
int main(void) {
	double a[5] = { 3,2,2,3,5 };
	double b[5] = { 0,0,0,0,0 };
	int i,j,k;
	k = 0;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (a[i] > a[j]) {
				k += 1;
			}
		}
		b[k] = a[i];
		k = 0;
	}
	f(b);
	for (i = 0; i < 5; i++) {
		printf("%lf\n", b[i]);
	}
	return 0;
}
void f(double arr[]) {
	int i;
	for (i = 0; i < 4; i++) {
		if (arr[i] != 0 && arr[i + 1] == 0) {
			arr[i + 1] = arr[i];
		}
	}
}