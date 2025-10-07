#include<stdio.h>
int main(void) {
	int i, j;
	for (i = 1; i <= 6; i++) {
		for (j = 'F'; j >= 'F' - i + 1; j--) {
			printf("%c", j);
		}
		printf("\n");
	}
	return 0;
}