#include<stdio.h>
int main(void) {
	char a, b;
	int c;
	scanf_s("%c", &a);
	getchar();
	scanf_s("%c", &b);
	getchar();
	scanf_s("%d", &c);
	if (a == 'A') {
		if (b == 'N') {
			if (c == 2) {
				printf("A320");
			}

		}
		if (b == 'W') {
			if (c == 2) {
				printf("A350");
			}
			if (c == 4) {
				printf("A380");
			}
		}

	}
	if (a == 'B') {
		if (b == 'N') {
			if (c == 2) {
				printf("B737");
			}

		}
		if (b == 'W') {
			if (c == 2) {
				printf("B787");
			}
			if (c == 4) {
				printf("B747");
			}

		}

	}
	if (a == 'C') {
		printf("C919");

	}
	return 0;
}