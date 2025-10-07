#include<stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {
	int tr[5] = { 0,0,0,0,0};
	int yr[5] = { 0,0,0,0,0 };
	int n, m, k;
	int T,q;
	
	scanf_s("%d", &T);
	for (q = 0; q < T; q++) {
		scanf_s("%d %d %d", &n, &m, &k);
		int i;
		int num1 = 0;
		int num2 = 0;
		int temp;
		int now[4];
		int all = 0;
		getchar();
		for (i = 0; i < n; i++) {
			temp = getchar();
			if (temp == 'C' && tr[4] == 0) {
				tr[0] = tr[4] = 1;
				all += 1;
			}
			else if (temp == 'D' && tr[0] == 1 && tr[1] == 0) {
				tr[1] = 1;
				all += 1;
			}
			else if (temp == 'N' && tr[1] == 1 && tr[2] == 0) {
				tr[2] = 1;
				all += 1;
			}
			else if (temp == 'L' && tr[2] == 1 && tr[3] == 0) {
				for (i = 0; i < 5; i++) {
					tr[i] = 0;
				}
				num1 += 1;
				all += 1;
			}
			if (all == m) {
				break;
			}
		}
		all = 0;
		getchar();
		for (i = 0; i < n; i++) {
			temp = getchar();
			if (temp == 'C' && yr[1] == 1) {
				for (i = 0; i < 4; i++) {
					yr[i] = 0;
				}
				all += 1;
			}
			else if (temp == 'D' && yr[2] == 1 && yr[1] == 0) {
				yr[1] = 1;
				all += 1;
			}
			else if (temp == 'N' && yr[3] == 1 && yr[2] == 0) {
				yr[2] = 1;
				all += 1;
			}
			else if (temp == 'L' && yr[3] == 0 && yr[4] == 0) {
				yr[3] = 1;
				yr[4] = 1;
				all += 1;
			}
			if (all == k) {
				break;
			}
		}
		int wh = 0;
		for (i = 0; i < 4; i++) {
			if (tr[i] + yr[i] >= 1) {
				wh += 1;
			}
		}
		int fin = 0;
		if (wh == 4) {
			fin += 1;
		}
		fin += num1;
		fin += num2;
		printf("%d", fin);
	}
	return 0;
}