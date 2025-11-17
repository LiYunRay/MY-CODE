#include<stdio.h>
int arr[100000], brr[100000], ope[100000];
int main(void) {
	int a, i, o, aim, now;
	o = 0;
	aim = 0;
	scanf_s("%d", &a);

	for (i = 0; i < a; i++) scanf_s("%d", &arr[i]);
	for (i = 0; i < a; i++) scanf_s("%d", &brr[i]);
	getchar();
	for (i = 0;; i++) {
		now = getchar();
		if (now == ']') break;
		else if (now == '[') continue;
		else if (now == 97) {
			ope[o] = 1;
			o += 1;
		}
		else if (now == 98) {
			ope[o] = 2;
			o += 1;
		}
		else if (now >= 48 && now <= 57)aim = aim * 10 + (now - 48);

	}
	int fin = aim;
	for (i = o-1; i >= 0; i--) {
		if (ope[i] == 1) fin = arr[fin - 1];
		else if (ope[i] == 2) fin = brr[fin - 1];
	}
	printf("%d", fin);
	return 0;
}