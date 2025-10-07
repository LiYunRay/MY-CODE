#include<stdio.h>
float l(float a, float b);
int main(void) {
	float a, b;
	printf("please input two real numbers\n");
	while (scanf_s("%f %f", &a, &b) == 2) {
		printf("%f\n", l(a,b));
	}
	return 0;
}
float l(float a,float b) {
	float c;
	c = (a - b) / a / b;
	return c;
}