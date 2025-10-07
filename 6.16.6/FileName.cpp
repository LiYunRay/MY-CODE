#include<stdio.h>
int main(void) {
	int max, min;
	int i;
	scanf_s("%d %d", &min,&max);
	for (i = min; i <= max; i++) {
		printf("%d,%d,%d\n", i, i * i, i * i * i);
	}
	return 0;
}