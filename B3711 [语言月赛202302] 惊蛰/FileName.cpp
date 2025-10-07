#include<stdio.h>
int f(unsigned long long);
int arr[20];
unsigned long long num[100];
int main(void) {
	int n;
	scanf_s("%d", &n);

	int i;
	for (i = 0; i < n; i++) {
		scanf_s("%llu", &num[i]);
	}
	for (i = 0; i < n; i++) {
		if (f(num[i]) == 1) {
			printf("Yes\n");
		}
		else {
			printf("No\n");
		}
	}
	return 0;
}
int f(unsigned long long a) {
	int i = 0;
	int len;
	int fin = 0;
	while (a >= 10) {
		arr[i] = a % 10;
		a = a / 10;
		i++;
	}
	len = i;
	arr[len] = a;

	if (arr[len] == 4 || arr[len] == 8 || arr[0] == 4 || arr[0] == 8||arr[0]==0) {
		fin = 1;
	}


	for (i = 1; i <= len; i++) {
		if ((10 * arr[i] + arr[0]) % 4 == 0) {
			fin = 1;
		}
	}
	for (i = 0; i < len; i++) {
		if ((arr[i] + 10 * arr[i + 1]) % 4 == 0) {
			fin = 1;
		}
	}
	return fin;
}
