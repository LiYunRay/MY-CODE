#include<stdio.h>
int main(void) {
	float hours, ext;
	float get, tax, final;
	printf("please input working hours\n");
	scanf_s("%f", &hours);
	if (hours <= 40) {
		get = hours * 10;
	}
	else {
		get = (hours + (hours - 40) * 0.5) * 10;
	}
	if (get <= 300) {
		tax = get * 0.15;
	}
	else if (get > 300 && get <= 450) {
		tax = 300 * 0.15 + (get - 300) * 0.2;
	}
	else {
		tax = 300 * 0.15 + 150 * 0.2 + (get - 450) * 0.25;
	}
	final = get - tax;
	printf("%f %f %f", get, tax, final);
	return 0;

}