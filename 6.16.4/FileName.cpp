#include<stdio.h>
int main(void) {
	int i, j;
	for (i = 1; i <= 6; i++) {
		for (j = 'A' + i * (i - 1) / 2; j <= 'A'+i * (i + 1) / 2-1; j++) {
			printf("%c", j);
		}
		printf("\n");
	}
	return 0;
}