#include<stdio.h>
int main(void) {
	int n, m;
	scanf_s("%d %d", &n, &m);
	int i=0, j = 0;
	for (j = 0; j < m; j++) {
		if (j % 4 == 1) putchar('.');
		else putchar('x');

	}
	printf("\n");
	for (i = 1; i < n - 1; i++) {
		for (j = 0; j < m; j++) {
			if (j % 2 == 0) putchar('x');
			else putchar('.');
			
		}
		printf("\n");
	}
	for (j = 0; j < m; j++) {
		if (j % 4 == 3) putchar('.');
		else putchar('x');

	}
}