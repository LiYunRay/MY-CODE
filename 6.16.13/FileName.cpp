#include<stdio.h>
int main(void) {
	int numbers[8];
	int i,a;
	a = 1;
		for (i = 0; i <= 7; i++) {
		a = a * 2;
		numbers[i] = a;
	}
	i = 0;
	do {
		printf("%d ", numbers[i]);
		i += 1;
	} while (i <= 7);
	return 0;
}