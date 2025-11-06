#include<stdio.h>
#include<stdlib.h>
long long itemweight[100000];
long long itemvalue[100000];
int num = 0;
void f(int,int,int);    
long long max(long long, long long);
long long* fin;
int main(void) {
	int n, W;
	scanf_s("%d %d", &n, &W);
	int i,t;
	int* v, * w, * m;
	v = (int*)malloc(n * sizeof(int));
	w = (int*)malloc(n * sizeof(int));
	m = (int*)malloc(n * sizeof(int));
	fin = (long long*) malloc(W * sizeof(long long));
	for (i = 0; i < n; i++) {
		scanf_s("%d %d %d", &v[i], &w[i], &m[i]);
	}
	for (i = 0; i < 100000; i++) {
		itemweight[i] = 0;
		itemvalue[i] = 0;
	}
	for (i = 0; i < n; i++) {
		f(v[i], w[i], m[i]);
	}
	for (i = 0; i < W; i++) {
		fin[i] = 0;
	}
	for (i = 0; i <= num; i++) {
		for (t = W - 1; t >= itemweight[i]; t--) {
			fin[t] = max(fin[t], fin[t - itemweight[i]] + itemvalue[i]);
		}
		if (W >= itemweight[i]) {
			fin[itemweight[i] - 1] = max(fin[itemweight[i] - 1], itemvalue[i]);
		}
	}
	printf("%lld", fin[W - 1]);
	free(fin);
	free(w);
	free(m);
	free(v);
	return 0;
}
void f(int v, int w, int m) {
	int temp = 0;
	int now = 1;
	while (now <= m) {
		m -= now;
		itemweight[num] = now * w;
		itemvalue[num] = now * v;
		num += 1;
		now *= 2;
	}
	if (m != 0) {


		itemweight[num] = m * w;
		itemvalue[num] = m * v;
		num += 1;
	}
}
long long max(long long a, long long b) {
	if (a >= b) {
		return a;
	 }
	else {
		return b;
	}
}