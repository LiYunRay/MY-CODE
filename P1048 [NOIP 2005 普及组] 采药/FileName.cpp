#include<stdio.h>
int arr[100][1000];
int value[100];
int time[100];
int f(int,int);
int max(int, int);
int main(void) {
	int t, m;
	scanf_s("%d %d", &t, &m);
	int i,j;
	for (i = 0; i < 100; i++) {
		for (j = 0; j < 1000; j++) {
			arr[i][j] = -1;
		}
	}
	for (i = 0; i < m; i++) {
		scanf_s("%d %d",&time[i], &value[i]);
	}
	int fin;
	fin = f(m, t);
	printf("%d", fin);
	return 0;

}
int f(int m, int t) {
	if (t <= 0||m<=0) {
		return 0;
	}
	else {
		if (m == 1) {
			if (t <= 0) {
				return 0;
			}
			else {
				if (t >= time[0]) {
					arr[0][t - 1] = value[0];
				}
				else {
					arr[0][t - 1] = 0;
				}
			}
		}
		if (arr[m - 1][t - 1] != -1) {
			return arr[m - 1][t - 1];
		}
		else {
			int fin;
			if (t >= time[m - 1]) {
				fin = max(f(m - 1, t), f(m - 1, t - time[m - 1]) + value[m - 1]);
			}
			else {
				fin = f(m - 1, t);
			}
			arr[m - 1][t - 1] = fin;
			return fin;
		}
	}
}
int max(int a, int b) {
	if (a >= b) {
		return a;
	}
	else {
		return b;
	}
}