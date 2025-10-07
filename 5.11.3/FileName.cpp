#include<stdio.h>
#define week_days 7
int main(void) {
	int a, b, c;
	scanf_s("%d", &a);
	while (a > 0) {
		b = a / week_days;
		c = a % week_days;
		printf("%d days are %d weeks,%d days\n",a,b,c);
		scanf_s("%d", &a);
	}
	return 0;
}