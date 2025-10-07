#include<stdio.h>
int main(void) {
	int a;
	scanf_s("%d", &a);
	int b = a + 10;
		while (a <= b) {
			printf("%d\n", a);
			a++;
	}
		return 0;
}