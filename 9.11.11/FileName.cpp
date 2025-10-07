#include<stdio.h>
int main(void) {
	int a, b, c;
	a = b = 1;
	int i;
	int n;
	scanf_s("%d", &n);
	if (n == 1||n==2) {
		printf("1");
	}
	if (n >= 3) {
		for (i = 1; i <= n - 2; i++) {
			c = a + b;
			a = b;
			b = c;
		}
		printf("%d", c);
	}
}