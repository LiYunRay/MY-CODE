#include<stdio.h>
int main(void) {
	int k;
	scanf_s("%d", &k);
	int n;
	double temp = 0;
	if (k == 1) {
		printf("2");
	}
	else {
		for (n = 1; temp < k; n++) {
			temp += 1.00 / n;
		}

		printf("%d", n - 1);
	}
	return 0;
} 