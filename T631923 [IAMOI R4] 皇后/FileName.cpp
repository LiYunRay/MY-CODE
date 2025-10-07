#include<stdio.h>
int main(void) {
	int T;
	int n, m, x1, y1, x2, y2;
	scanf_s("%d", &T);
	int q, i, j,fin;
	for (q = 0; q < T; q++) {
		scanf_s("%d %d %d %d %d %d", &n, &m, &x1, &y1, &x2, &y2);
		if (x1 == x2 && y1 == y2) {
			fin = 0;
		}
		else if (x1 == x2 || y1 == y2) {
			if (x1 == x2) {
				if (y1 - y2 == 1 || y1 - y2 == -1) {
					fin = 1;
				}
				else if ((y1 - y2) % 2 == 0) {
					if (((x1 + (y2 - y1) / 2) <= n && (x1 + (y2 - y1) / 2) >= 1) || ((x1 - (y2 - y1) / 2) <= n && (x1 - (y2 - y1) / 2) >= 1)) {
						fin = 2;
					}
					else {
						fin = 3;
					}
				}
				else {
					fin = 3;
				}
			}
			else if (y1 == y2) {
				if ((x1 - x2) % 2 == 0) {
					if (x1 - x2 == 1 || x1 - x2 == -1) {
						fin = 1;
					}
					else if (((y1 + (x2 - x1) / 2) <= m && (y1 + (x2 - x1) / 2) >= 1) || ((y1 - (x2 - x1) / 2) <= m && (y1 - (x2 - x1) / 2) >= 1)) {
						fin = 2;
					}
					else {
						fin = 3;
					}
				}
				else if (x1 - x2 == 1 || x1 - x2 == -1) {
					fin = 1;
				}
				else {
					fin = 3;
				}
			}

		}
		else {
			if ((x1 - x2 == 1 || x1 - x2 == -1)&& (y1 - y2 == 1 || y1 - y2 == -1)) {
				fin = 1;
			}
			else {
				fin = 2;
			}
		}
		printf("%d\n", fin);

	}
	return 0;
}