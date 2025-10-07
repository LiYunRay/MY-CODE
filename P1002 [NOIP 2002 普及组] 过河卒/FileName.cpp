#include<stdio.h>
#include<stdlib.h>
int main(void) {
	long long a[21][21];
	int x, y, m, n, i, j;
	scanf_s("%d %d %d %d",&x,&y,&m,&n);
	for (i = 0; i < 21; i++) {
		for (j = 0; j < 21; j++) {
			if (abs(i - m ) == 1 && abs(j - n ) == 2) {
				a[i][j] = -1;
			}
			else if (abs(i - m ) == 2 && abs(j - n ) == 1) {
				a[i][j] = -1;
			}
			else if (i == m  && j == n ) {
				a[i][j] = -1;
			}
			else {
				a[i][j] = 0;
			}
		}
	}

	for (i = 0; i <=x; i++) {
		for (j = 0; j <= y; j++) {
			if (i == 0 && j == 0) {
				a[0][0] = 1;
			}
			else {
				if (a[i][j] < 0) {
					a[i][j] = 0;
				}
				else {
					if (i == 0) {
						a[i][j] = a[i][j - 1];
					}
					else if (j == 0) {
						a[i][j] = a[i - 1][j];
					}
					else {
						a[i][j] = a[i][j - 1] + a[i - 1][j];
					}
				}
			}
		}
	}
	printf("%lld", a[x ][y]);
	return 0;
}