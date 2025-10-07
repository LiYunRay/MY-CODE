#include<stdio.h>
int main(void) {
	char numbers[8];
	int i;
	for (i = 0; i <= 7; i++) {
		scanf_s("%d", &numbers[i]);
	}
	for (i = 7; i >= 0; i--) {
		printf("%d ", numbers[i]);
	}
	return 0;
}