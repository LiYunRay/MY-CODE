#include<stdio.h>
int prime(int);
int main(void) {
	int a,i;
	scanf_s("%d", &a);
	if (a <= 0) {
		return 0;
	}
	for (i = 2; i <= a; i++) {
		if (prime(i) == 1) {
			printf("%d ", i);
		}
		else {
			continue;
		}
	}
	return 0;
}

int prime(int m) {
	int j,t=0;
	for (j = 2; j * j <= m; j++) {
		if ((m % j) == 0) {
			t += 1;
		}
	}
	if (t == 0) {
		return 1;
	}
	else {
		return 0;
	}
}
