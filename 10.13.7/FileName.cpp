#include<stdio.h>
void copy_arr(double[], double[], int a);
int main(void) {
	int i, j;
	double arr[3][3],aim[3][3];
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			arr[i][j] = (i+1)*(j+1);
		}
	}
	for (i = 0; i < 3; i++) {
		copy_arr(aim[i], arr[i], 3);
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			printf("%lf %lf\n", arr[i][j], aim[i][j]);
		}
	}
	return 0;
}



void copy_arr(double target1[], double source[], int a) {
	int i;
	for (i = 0; i < a; i++) {
		target1[i] = source[i];
	}
}