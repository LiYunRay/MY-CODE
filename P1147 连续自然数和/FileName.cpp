#include<stdio.h>
int main(void) {
	int n;
	scanf_s("%d", &n);
	int i,j;
	i = j = 0;
	int temp = 0;
	while (i < n) {
		if (temp == n) printf("%d %d\n", i, j);
		if (temp <=n) {
			j += 1;
			temp += j;
		}
		else if (temp > n) {
			temp -= i;
			i += 1;
		}

	}

	return 0;
}