#include<stdio.h>
char eat[5000];
short arr[5000][5000];
long long num[5000];
char top[5000];
int f(int);
int main(void) {
	int n;
	long long m;
	int i, j;
	int a, b;
	long long fin = 0;
	scanf_s("%d %lld", &n, &m);
	for (i = 0; i < 5000; i++) {
		for (j = 0; j < 5000; j++) {
			arr[i][j] = 0;
		}
		num[i] = -1;
		top[i] = 1;
		eat[i] = 0;
	}
	for (i = 0; i < m; i++) {
		scanf_s("%d %d", &a, &b);
		arr[a - 1][b - 1] = 1;
		top[a - 1] = 0;
		eat[b - 1] = 1;

	}
	for (i = 0; i < n; i++) {
		if (top[i]) {
			fin += f(i) % 80112002;

			fin = fin % 80112002;
		}
	}
	fin = fin % 80112002;
	printf("%lld", fin);
	
	return 0;

}


int f(int n) {
	int i;
	int fin = 0;
	if (num[n] != -1) {
		return num[n];
	}
	else {
		if (eat[n] == 0) {
			num[n] = 1;
			return 1;
		}
		for (i = 0; i < 5000; i++) {
			if (arr[i][n] != 0) {
				fin += f(i) % 80112002;
				fin = fin % 80112002;

			}
		}
		fin = fin % 80112002; 
		num[n] = fin;
		return fin;
	}
}