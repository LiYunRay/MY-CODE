#include<stdio.h>
int main(void) {
	int type,max,earn;
	float tax;
	scanf_s("%d", &type);
	switch (type) {
	case 1:max = 17850; break;
	case 2:max = 23900; break;
	case 3:max = 29750; break;
	case 4:max = 14975; break;
	default:return 0;
	}
	scanf_s("%d", &earn);
	if (earn <= 0) {
		return 0;
	}
	else if (earn <= max&&earn>0) {
		tax = earn * 0.15;
	}
	else {
		tax = max * 0.15 + (earn - max) * 0.28;
	}
	printf("%f", tax);
	return 0;
}