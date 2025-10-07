#include<stdio.h>
int main(void) {
	char letter;
	int i, j,k;
	printf("please input a letter\n");
	scanf_s("%c", &letter);
	i = letter - 64;
	for (j = 1;j<= i; j++) {
		for (k = 1; k <= i - j; k++) {
			printf(" ");
		}
		for (k = 'A'; k <= 'A' + j - 1; k++) {
			printf("%c", k);
		}
		for (k = 'A' + j - 2; k >= 'A'; k--) {
			printf("%c", k);
		}
		for (k = 1; k <= i - j; k++) {
			printf(" ");
		}
		printf("\n");
	}
	return 0;
}