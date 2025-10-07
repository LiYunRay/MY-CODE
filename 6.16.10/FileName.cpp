#include<stdio.h>
int main(void) {
	int max, min,sum;
	sum = 0;
	int i;
	printf("please input max and min\n");
	scanf_s("%d %d", &max, &min);
	while (max > sum) {
		for (i = min; i <= max; i++) {
			sum = sum + i * i;
		}
		printf("%d\n", sum);
		scanf_s("%d %d", &max, &min);
	}
	return 0;

}