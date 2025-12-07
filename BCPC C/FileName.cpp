#include<stdio.h>
long long int n, t;
int main(void) {
	int q;
	scanf("%d", &q);
	int i;
	long long int fin;
	for (i = 0; i < q; i++) {
		scanf("%lld %lld", &n, &t);
		if (n <= 2) fin = t * n;
		else if (n == 3)fin = 3 * t - 2;
		else if (n == 4) fin = 4 * t - 4;
		else if (n <= 4 * (t / 2 - 1))fin = 4 * t - 4 + t / 2 * (n - 4);
		
		else fin = 4 * t - 4 + t / 2 * 4 * (t / 2 - 2);
		
		printf("%lld\n", fin);
	}
	return 0;
	
}