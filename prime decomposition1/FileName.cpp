#include<stdio.h>
int p(int);
int exp(int, int);
int main(void) {
	int a, i;
	scanf_s("%d", &a);
	for (i = 2; i <= a; i++) {
		if (p(i) == 0) {
			continue;
		}
		if (p(i) == 1) {
			if (exp(a, i) != 0) {
				printf("%d ", i);
				printf("%d\n", exp(a, i));
			}
		}
	}
}int p(int a) {
	int j,k=0;
	if (a == 2) {
		return 1;
	}
	if (a == 3) {
		return 1;
	}
	if (a > 3) {
		for (j = 2; j * j <= a; j++) {
			if (a % j == 0) {
				k = 0;
				break;
			}
			else {
				k = 1;
			}

		}
		return k;
	}
}
int exp(int a, int i) {
	int k=0;
	while (a % i == 0 && a != i) {
		k += 1;
		a = a / i;
	}
	if (a == i) {
		k += 1;
	}
	return k;
}