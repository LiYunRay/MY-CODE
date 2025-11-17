#include<stdio.h>
int main(void) {
	int a, b, c;
	scanf_s("%d %d %d", &a, &b, &c);
	int fin;
	fin = 0.2 * a + 0.3 * b + 0.5 * c;
	printf("%d", fin);
	return 0;
}