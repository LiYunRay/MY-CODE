#include<stdio.h>
int main(void) {
	int k;
	for (k = 1, printf("%dhi\n", k); printf("k=%d\n", k), k * k < 26; k += 2, printf("now k=%d\n", k)) {
		printf("k is %d in the loop\n", k);
	}
	return 0;
}