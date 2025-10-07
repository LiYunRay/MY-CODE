#include<stdio.h>
void copy_arr(double[], double[], int a);
int main(void) {
	double arr[7] = { 1,2,3,4,5,6,7 };
	double aim[3];
	int i;
	copy_arr(aim, arr + 2, 3);
	for (i = 0; i < 3; i++) {
		printf("%lf %lf\n", aim[i], arr[i + 2]);
	}
	return 0;
}
void copy_arr(double target1[], double source[], int a) {
	int i;
	for (i = 0; i < a; i++) {
		target1[i] = source[i];
	}
}