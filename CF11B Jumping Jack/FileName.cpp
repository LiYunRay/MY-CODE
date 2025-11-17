#include<stdio.h>
int main(void) {
	long long x;
	scanf_s("%lld", &x);
	if (x < 0) x = -x;
	int temp, i=1;
	temp = 0;
	int fin = 0;
	while (temp < x) {
		temp += i;
		i += 1;
		fin += 1;
	}
	if (temp == x) printf("%d", fin);
	else {
		int l = temp - x;
		if (l % 2 == 0) printf("%d", fin);
		else {
			if (i % 2 == 1) printf("%d", fin + 1);
			else printf("%d", fin + 2);
		}
	}
	return 0;

}