#include<stdio.h>
int main(void) {
	float a=100;
	int i = 0;
	while (a > 0) {
		a = a * 1.08 - 10;
		i += 1;
	}
	printf("%d", i);
	return 0;
}