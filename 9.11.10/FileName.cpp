#include<stdio.h>
#include<string.h>
void to(int, int);
int main(void) {
	int a, b;
	scanf_s("%d %d", &a, &b);
	to(a, b);
	return 0;
}
void to(int a, int b) {
	if (a >= b) {
		int c = a % b;
		to((a - c) / b, b);
		printf("%d", c);
	}
	else {
		printf("%d", a);
	}
}