#include<stdio.h>
double ever(double[]);
double eve(double[][5]);
double max(double[][5]);
int main(void) {
	double arr[3][5];
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 5; j++) {
			scanf_s("%lf", &arr[i][j]);
		}
	}
	for (i = 0; i < 3; i++) {
		printf("%lf\n",ever(arr[i]));
	}
	printf("%lf\n", eve(arr));
	printf("%lf", max(arr));

}
double ever(double arr[]) {
	double a=0;
	int i;
	for (i = 0; i < 5; i++) {
		a += arr[i];
	}
	a = a / 5;
	return a;
}
double eve(double arr[][5]) {
	double a = 0;
	int i, j;
	for (i = 0; i < 3; i ++ ) {
		for (j = 0; j < 5; j++) {
			a += arr[i][j];
		}
	}
	a = a / 15;
	return a;
}
double max(double arr[][5]) {
	double a = arr[0][0];
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 5; j++) {
			if (arr[i][j] > a) {
				a = arr[i][j];
			}
		}
	}
	return a;
}