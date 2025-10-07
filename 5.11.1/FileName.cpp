#include<stdio.h>
#define time_minute 60
int main(void) {
	int a, b, c;
	scanf_s("%d", &a);
	while (a > 0) {
		b = a / time_minute;
		c = a % time_minute;
		printf("%d %d\n", b, c);
		scanf_s("%d", &a);
	}
	return 0;
}