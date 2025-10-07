#include<stdio.h>
int main(void) {
	int a, n, m, x;
	int i;
	scanf_s("%d %d %d %d", &a, &n, &m, &x);
	int arr[20][2];
	int t[20][2];
	arr[0][0] = a;
	arr[0][1] = 0;
	arr[1][0] = 0;
	arr[1][1] = 0;
	t[0][0] = 0;
	t[0][1] = 0;
	t[1][0] = 1;
	t[1][1] = -1;
	for (i = 2; i < n-1; i++) {
		arr[i][0] = arr[i - 1][0] + arr[i - 2][0];
		t[i][0] = t[i - 1][0] + t[i - 2][0];
		arr[i][1] = -arr[i - 1][0] ;
		t[i][1] = -t[i - 1][0] ;
	}
	int p, q;
	p = q = 0;
	for (i = 0; i < n-1; i++) {
		p += arr[i][0];
		p += arr[i][1];
		q += t[i][0];
		q += t[i][1];
	}
	int in;
	if (q == 0) {
		in = 0;
	}
	else {
		in = (m - p) / q;
	}
	p = q = 0;
	for (i = 0; i < x; i++) {
		p += arr[i][0];
		p += arr[i][1];
		q += t[i][0];
		q += t[i][1];
	}
	printf("%d", p + q * in);
	return 0;
}