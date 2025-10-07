#include<stdio.h>
int main(void) {
	int input,evens,odds,a,b;
	evens = odds = a=b=0;
	float eve1, eve2;
	scanf_s("%d", &input);
	if (input == 0) {
		return 0;
	}
	else {
		while (input != 0) {
			if ((input % 2) == 0) {
				evens = evens + input;
				a += 1;
			}
			else {
				odds = odds + input;
				b += 1;
			}
			scanf_s("%d", &input);

		}
		eve1 = evens / a;
		eve2 = odds / b;
		printf("%d %f %d %f", a, eve1, b, eve2);
		return 0;
	}
}