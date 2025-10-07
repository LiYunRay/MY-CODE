#include<stdio.h>
#include<stdlib.h>
int main(void) {
	int T, p;
	int n, m, x, y;
	int i, j;
	int xm[100][2];
	int ym[100][2];
	int all[300][2];
	scanf_s("%d", &T);
	int ynow = 1;
	int allnow = 0;
	int fin;
	for (p = 0; p < T; p++) {
		for (i = 0; i < 300; i++) {
			all[i][0] = all[i][1] = 0;

		}
		for (i = 0; i < 100; i++) {
			xm[i][0] = xm[i][1] = ym[i][0] = ym[i][1] = 0;

		}
		fin = 0;
		allnow = 0;
		ynow = 1;
		scanf_s("%d %d %d %d", &n, &m, &x, &y);
		for (i = 0; i < x; i++) {
			scanf_s("%d %d", &xm[i][0], &xm[i][1]);
		}
		for (i = 0; i < y; i++) {
			scanf_s("%d %d", &ym[i][0], &ym[i][1]);
		}
		for (i = 0;  i < x; i++) {
			for (j = ynow - 1;j<y ; j++) {
				if (xm[i][0] > ym[j][1]) {
					continue;
				}
				else if (xm[i][0] <= ym[j][1] && ym[j][1] <= xm[i][1] && xm[i][0] >= ym[j][0]) {
					all[allnow][0] = xm[i][0];
					all[allnow][1] = ym[j][1];
					allnow += 1;

				}
				else if (xm[i][0] <= ym[j][1] && ym[j][1] <= xm[i][1] && xm[i][0] <= ym[j][0] && ym[j][0] <= xm[i][1]) {
					all[allnow][0] = ym[j][0];
					all[allnow][1] = ym[j][1];
					allnow += 1;

				}
				
				else if (xm[i][0] <= ym[j][0] && ym[j][0] <= xm[i][1] && xm[i][1] <= ym[j][1]) {
					all[allnow][0] = ym[j][0];
					all[allnow][1] = xm[i][1];
					allnow += 1;
				}
				else if (ym[j][0] <= xm[i][0] && ym[j][1] >= xm[i][1]) {
					all[allnow][0] = xm[i][0];
					all[allnow][1] = xm[i][1];
					allnow += 1;
				}
				else {
					ynow = j;
					break;
				}
			}
		}
		for (i = 0; i <= allnow; i++) {
			if (all[i][1] - all[i][0] >= m-1) {
				fin += all[i][1] - all[i][0] + 2-m;
			}
		}

		printf("%d\n", fin);
	}
}

