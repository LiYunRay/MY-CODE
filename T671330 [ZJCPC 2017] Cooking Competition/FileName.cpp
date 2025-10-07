#include<stdio.h>
int main(void) {
	int t, j,i,a,b;
	int n;
	int arr[20];
	scanf_s("%d", &t);
	for (j = 0; j < t; j++) {
		scanf_s("%d", &n);
		for (i = 0; i < n; i++) {
			scanf_s("%d", &arr[i]);
		}
		a = b = 0;
		for (i = 0; i < n; i++) {
			if (arr[i] == 1) {
				a += 1;
			}
			else if (arr[i] == 2) {
				b += 1;
			}
			else if (arr[i] == 3) {
				a += 1;
				b += 1;
			}
			else {
				a -= 1;
				b -= 1;
			}

		}
		if (a > b) {
			printf("Kobayashi\n");
		}
		else if (a < b) {
			printf("Tohru\n");

		}
		else {
			printf("Draw\n");
		}
	}
	return 0;

}