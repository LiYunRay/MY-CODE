#include<stdio.h>
void copy_arr(double[], double[], int a);
void copy_ptr(double[], double[], int a);
void copy_ptrs(double[], double *p, double *q);
void print(double[],int);
int main(void) {
	double source[5] = { 1.1,2.2,3.3,4.4,5.5 };
	double target1[5];
	double target2[5];
	double target3[5];
	copy_arr(target1, source, 5);
	copy_ptr(target2, source, 5);
	copy_ptrs(target3, source, source + 5);
	print(target1,5);
	print(target2,5);
	print(target3,5);
	return 0;
}
void copy_arr(double target1[], double source[], int a) {
	int i;
	for (i = 0; i < a; i++) {
		target1[i] = source[i];
	}
}
void copy_ptr(double target2[], double source[], int a) {
	int i;
	for (i = 0; i < a; i++) {
		*(target2 + i) = *(source + i);
	}
}
void copy_ptrs(double target3[],double *p ,double *q ) {
	int i;
	for (i = 0; p + i < q; i++) {
		target3[i] = *(p + i);
	}

}
void print(double arr[], int a) {
	int i;
	for (i = 0; i < a; i++) {
		printf("%lf ", arr[i]);
	}
	printf("\n");
}