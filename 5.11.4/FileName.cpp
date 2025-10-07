#include<stdio.h>
int main(void) {
	float a, c;
	int b;
	scanf_s("%f", &a);
	while (a > 0) {
		b = a/30.48;
		c = (a - b * 30.48) / 2.54;
		printf("%.1fcm = %d feet,%.1f inches\n", a, b, c);
		scanf_s("%f", &a);
     }
	return 0;
}