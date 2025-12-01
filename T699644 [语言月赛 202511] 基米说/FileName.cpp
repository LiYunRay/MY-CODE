#include<stdio.h>
int main(void) {
	int x1, x2, x3;
	int y1, y2, y3;
	scanf_s("%d %d %d", &x1, &x2, &x3);
	scanf_s("%d %d %d", &y1, &y2, &y3);
	int fin = 0;
	if ((x1 * y1 + x2 * y2 + x3 * y3) == 0) fin = 1;
	if (fin == 0)printf("Non-Orthogonal");
	else printf("Orthogonal");
	return 0;

}