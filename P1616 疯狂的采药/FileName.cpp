#include<stdio.h>
#include<stdlib.h>
long long max(long long, long long);
int main(void) {
	int t, m;
	int i,j;
	int* a, *b;
	long long* fin;
	scanf_s("%d %d", &t, &m);
	a = (int*)malloc(m*sizeof(int));
	b = (int*)malloc(m * sizeof(int));
	fin = (long long*)malloc(t * sizeof(long long));
	for (i = 0; i < m; i++) {
		scanf_s("%d %d", &a[i], &b[i]);
	}
	for (i = 0; i < t; i++) {
		fin[i] = 0;
	}
	for (i = 0; i < m; i++) {
		if (a[i] > t) {
			continue;
		}
		fin[a[i] - 1] = max(b[i], fin[a[i] - 1]);
		for (j = a[i]; j < t; j++) {
			fin[j] = max(fin[j - a[i]]+b[i], fin[j]);

		}
	}
	printf("%lld", fin[t - 1]);
	free(fin);
	free(b);
	free(a);
	return 0;
}
long long max(long long a, long long b) {
	if (a >= b) {
		return a;
	}
	else {
		return b;
	}
}