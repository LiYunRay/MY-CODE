#include<stdio.h>
#include<string.h>
void f(int[], int[]);
void print(int[]);
int main(void) {
	int a[3000], b[3000];
	int i;
	int in;
	scanf_s("%d", &in);
	for (i = 0; i < 3000; i++) {
		a[i] = b[i] = 0;
	}
	a[0] = 1;
	b[0] = 2;
	for (i = 1; i < in; i++) {
		f(a, b);
	}
	print(a);
	return 0;
}
void f(int a[], int b[]) {
	int i;
	int c[3000];
	for (i = 0; i < 3000; i++) {
		c[i] = b[i] ;
	}
	for (i = 0; i < 3000; i++) {
		if ((a[i] + b[i]) < 10) {
			b[i] = a[i] + b[i];
		}
		else {
			b[i + 1] += (a[i] + b[i]) / 10;
			b[i] = (a[i] + b[i]) % 10;
		}

	}
	for (i = 0; i < 3000; i++) {
		a[i] = c[i];
	}
}
void print(int a[]) {
	int len = 3000;
	int i;
	for (i = 2999; i >=0; i--) {
		if (a[i] == 0) {
			len--;
		}
		else {
			break;
		}
	}
	for (i = len - 1; i >= 0; i--) {
		printf("%d", a[i]);
	}
}