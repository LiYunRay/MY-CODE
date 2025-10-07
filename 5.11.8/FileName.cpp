#include<stdio.h>
int main(void) {
	int a, b,c;
	printf("This program computes moduli,\n");
	printf("Enter an integer to serve as the second operand:");
	scanf_s("%d", &a);
	printf("\nNow enter the first operand(<=0 to quit):");
	scanf_s("%d", &b);
	while (b > 0) {
		c = b % a;
		printf("\n%d %% %d is %d\n", b, a, c);
		printf("Now enter the first operand(<=0 to quit):");
		scanf_s("%d", &b);
	}
	return 0;
}