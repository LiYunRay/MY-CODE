#include<stdio.h>
char arr[100];
char fin[500];
char temp[505];
char o[505];
char p[505];
void f(char*);
void g(char*);
int main(void) {
	int i,j;
	int n;
	int len;
	scanf_s("%d", &n);
	len = 1/3.3219280 * n+1;
	for (i = 0; i < 100; i++) arr[i] = 0;
	int loc = 0;
	while (n > 0) {
		if (n % 2 == 1) {
			arr[loc] = 1;
		}
		loc += 1; n /= 2;
	}
	temp[0] = 2;
	fin[0] = 1;
	for (i = 0; i < 100; i++) {
		if (arr[i] == 1) g(temp);
		f(temp);
	}
	fin[0] -= 1;
	
	
	printf("%d\n", len);
	for (i = 499; i >= 0; i--) {
		printf("%d", fin[i]);
		if (i % 50 == 0) printf("\n");
	}
	return 0;
}
void f(char temp[505]) {
	int i,j;
	for (i = 0; i < 500; i++) o[i] = 0;
	for (i = 0; i < 500; i++) {
		for (j = 0; j < 500; j++) {
			if ((i + j) < 500) {
				o[i + j] += temp[i] * temp[j];
			}
		}
		for (j = 0; j < 500; j++) {
			o[j + 1] += o[j] / 10;
			o[j] %= 10;
		}
	}
	for (i = 0; i < 500; i++) {
		temp[i] = o[i];
	}
}
void g(char temp[505]) {
	int i, j;
	for (i = 0; i < 500; i++) p[i] = 0;
	for (i = 0; i < 500; i++) {
		for (j = 0; j < 500; j++) {
			if ((i + j) < 500) {
				p[i + j] += fin[i] * temp[j];
			}
		}
		for (j = 0; j < 500; j++) {
			p[j + 1] += p[j] / 10;
			p[j] %= 10;
		}
	}
	for (i = 0; i < 500; i++) {
		fin[i] = p[i];
	}


}