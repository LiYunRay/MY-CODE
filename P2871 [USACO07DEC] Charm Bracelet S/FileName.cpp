#include<stdio.h>
#include<stdlib.h>
int max(int, int);
int main(void) {
	int N, M;
	scanf_s("%d %d", &N, &M);
	int i, t;
	int* m = (int*)malloc(N * sizeof(int));
	int* d = (int*)malloc(N * sizeof(int));
	for (i = 0; i < N; i++) {
		scanf_s("%d %d", &m[i], &d[i]);
	}
	int* fin = (int*)malloc(M * sizeof(int));
	for (i = 0; i < M; i++) {
		fin[i] = 0;
	}
	for (i = 0; i < N; i++) {
		for (t = M-1; t >= m[i]; t--) {
			fin[t] = max(fin[t], (fin[t - m[i]] + d[i]));
		}
		fin[m[i] - 1] = max(fin[m[i] - 1],d[i] );
	}
	printf("%d", fin[M - 1]);
	free(fin);
	free(d);
	free(m);
	return 0;
}
int max(int a, int b) {
	if (a >= b) {
		return a;
	}
	else {
		return b;
	}
}