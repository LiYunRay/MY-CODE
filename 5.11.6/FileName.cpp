#include<stdio.h>
int main(void) {
	int a, b, limit;
	a = 0;
	b = 0;
	scanf_s("%d", &limit);
	while (a++ < limit) {
		b = b + a * a;
	}
	printf("%d", b);
	return 0;
}
