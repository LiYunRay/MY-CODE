#include<stdio.h>
int main(void) {
	int s, v;
	scanf_s("%d %d", &s, &v);
	int cost;
	if (s % v == 0) {
		cost = s / v;
	}
	else {
		cost = s / v + 1;
	}
	int su;
	su = 8 * 60 - 10 - cost;
	int hours, min;
	if (su <= 0) {
		su += 24 * 60;
	}
	hours = su / 60;
	min = su % 60;
	if (hours < 10) {
		printf("0");
	}
	printf("%d", hours);
	printf(":");
	if (min < 10) {
		printf("0");
	}
	printf("%d", min);


}