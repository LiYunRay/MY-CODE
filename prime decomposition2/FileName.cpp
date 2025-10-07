#include<stdio.h>
int p(int);
int main(void) {
	int a, i;
	int all[100];
	scanf_s("%d", &a);
	int b = a;
	for (i = 0; i < 100; i++) {
		all[i] = 0;
	}
	while (a > 1) {
		for (i = 2; i <= a; i++) {
			if (p(i) == 1 && (a % i) == 0) {
				all[i] += 1;
				a = a / i;
				break;
			}
		}
	}
	        for (i = 0; i <= 20; i++) {
				if (all[i] != 0) {
					printf("%d %d\n", i, all[i]);
				}
			}
	     
		return 0;
}
int p(int a) {
	int j, k = 0;
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
