#include<stdio.h>
int main(void) {
	int count, sum,max;
	count = 0;
	sum = 0;
	scanf_s("%d", &max);
	while (count++ < max) {
		sum = sum + count;
	}
    printf("%d", sum);
	return 0;
}