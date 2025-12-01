#include<stdio.h>
int main(void) {
	int n, m, r, c;
	int x1, y1, x2, y2;
	scanf_s("%d %d %d %d", &n, &m, &r, &c);
	scanf_s("%d %d %d %d", &x1, &y1, &x2, &y2);
	if(r!=1)x1 = (x1 + 1) / r;
	if ((x2 + 1) % r == 0) x2 = ((x2 + 1) / r);
	else x2 = (x2 + 1) / r + 1;
	if(c!=1) y1 = (y1 + 1) / c;
	if ((y2 + 1) % c == 0) y2 = ((y2 + 1) / c);
	else y2 = (y2 + 1) / c + 1;
	int p, q;
	p = x2 - x1;
	q = y2 - y1;
	int fin = p * q;
	printf("%d", fin);
	return 0;
}