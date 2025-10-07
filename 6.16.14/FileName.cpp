#include<stdio.h>
int main(void) {
	double list1[8], list2[8];
	int i,j;
	for (i = 0; i <= 7; i++) {
		list2[i] = 0;
	}
	for (i = 0; i <= 7; i++) {
		scanf_s("%lf", &list1[i]);
	}
	for (i = 0; i <= 7; i++) {
		for (j = 0; j <= i; j++) {
			list2[i] = list2[i] + list1[j];
		}
	}
	for (i = 0; i <= 7; i++) {
		printf("%lf ", list1[i]);
	}
	printf("\n");
	for (i = 0; i <= 7; i++) {
		printf("%lf ", list2[i]);
	}
	return 0;
}