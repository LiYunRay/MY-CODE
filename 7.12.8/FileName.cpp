#include<stdio.h>
int main(void) {
	float hours, a;
	float get, tax, final;
	int input;
	printf("please input working hours\n");
	scanf_s("%f", &hours);
	start:printf("1 8.75       2 9.33        3 10.00     4 11.20     5    quit\n");
    scanf_s("%d", &input);
	switch (input) {
	case 1:a = 8.75; break;
	case 2:a = 9.33; break;
	case 3:a = 10.00; break;
	case 4:a = 11.20; break;
	case 5:return 0;
	default:goto start;
	}
    if (hours <= 40) {
		get = hours *a ;
	}
	else {
		get = (hours + (hours - 40) * 0.5) * a;
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