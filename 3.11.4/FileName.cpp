#include<stdio.h>
int main() {
	float a;
	scanf_s("%f", &a);
	printf("%f,%e\n", a, a);
	printf("%f,%e\n", a*100, a*100);
	return 0;
}