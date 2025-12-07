#include<stdio.h>
int main(void) {
	int n;
	scanf("%d", &n);
	int a1, b1, c1, a2, b2, c2;
	scanf("%d-%d-%d", &a1, & b1, &c1);
	scanf("%d-%d-%d", &a2, &b2, &c2);
	int i;
	int a, b, c, d;
	int fin = 0;
	int p = 365 * a1 + 30 * b1 + c1;
	int q = 365 * a2 + 30 * b2 + c2;
	for (i = 0; i < n; i++) {
		scanf("%d-%d-%d: %d", &a, &b, &c, &d);
		int temp = 365 * a + 30 * b + c;
		if (temp >= p && temp <= q) fin += d;
	}
	printf("%d", fin);
	return 0;
}