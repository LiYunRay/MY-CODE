#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char input[400000];
long long alines[100000];
long long blines[100000];
int main(void) {
	unsigned long long n;
	scanf_s("%llu", &n);
	unsigned long long j;
	for (j = 0; j < n; j++) {
		scanf_s("%lld", &alines[j]);
	}

	for (j = 0; j < n; j++) {
		scanf_s("%lld", &blines[j]);
	}

	for (j = 0; j < 400000; j++) {
		if ((scanf_s("%c", &input[j])) != 1) {
			break;
		}
		else {
			scanf_s("%c", &input[j]);
		}
	}

	unsigned long long size;
	size = strlen(input);
	for (j = size - 1; j >= 0; j--) {
		if ((input[j] == ']') && (input[j - 1] == ']')) {
			continue;
		}
	}
}