#include<stdio.h>
int min(long long, long long);
void f(long long*, long long*);
int main(void) {
	int T, q;
	long long a1, b1, c1;
	long long a2, b2, c2;
	long long num = 0;
	int x, y, z;
	scanf_s("%d", &T);
	for (q = 0; q < T; q++) {
		num = 0;
		scanf_s("%lld %lld %lld", &a1, &b1, &c1);
		scanf_s("%lld %lld %lld", &a2, &b2, &c2);
		x = min(a1, b2);
		y = min(b1, c2);
		z = min(c1, a2);
		a1 -= x;
		b2 -= x;
		b1 -= y;
		c2 -= y;
		c1 -= z;
		a2 -= z;
		num += x;
		num += y;
		num += z;
		f(&a1, &a2);
		f(&b1, &b2);
		f(&c1, &c2);
		num -= a1;
		num -= b1;
		num -= c1;
		printf("%lld\n", num);

	}
	return 0;
}
int min(long long a, long long b) {
	if (a >= b) {
		return b;
	}
	else {
		return a;
	}
}
void f(long long* h, long long* g) {
	int k = min(*h, *g);
	*h -= k;
	*g -= k;
}