#include<stdio.h>
int main(void) {
	long long int n, q;
	scanf_s("%lld %lld", &n, &q);

	long long int i;
	unsigned long long int numbers[3000];
	for (i = 0; i < n; i++) {
		scanf_s("%llu", &numbers[i]);
	}

	long long int J;
	long long int m[1000];
	for (J = 0; J < q; J++) {
		scanf_s("%lld", &m[J]);
	}

	long long int arr[1000];
	for (J = 0; J < q; J++) {
		for (i = 0; i < 1000; i++) {
			arr[i] = 0;
		}

		for (i = 0; i < n; i++) {
			arr[numbers[i] % m[J]] = 1;
		}

		long long int result = 0;
		for (i = 0; i < m[J]; i++) {
			if (arr[i] == 1) {
				result += 1;
			}
		}

		printf("%lld\n", result);
	}

	return 0;
}