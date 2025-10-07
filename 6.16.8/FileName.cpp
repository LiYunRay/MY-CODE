#include<stdio.h>
int main(void) {
	float a, b;
	printf("please input two real numbers\n");
	while (scanf_s("%f %f", &a, &b) == 2) {
		printf("%f\n", (a - b) / a / b);
	}
	return 0;
}