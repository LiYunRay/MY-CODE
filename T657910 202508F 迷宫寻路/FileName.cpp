#include<stdio.h>
int f(int, int,int ,int , int[][100]);
int main(void) {
	int arr[100][100];
	int i, j,  m, n,q;
	scanf_s("%d", &m);
	scanf_s("%d", &n);
	scanf_s("%d", &q);
	int a, b;
	for (a = 0; a < m; a++) {
		for (b = 0; b < n; b++) {
			scanf_s("%d", &arr[a][b]);
		}
	}
	for (a = 0; a < q; a++) {
		scanf_s("%d", &i);
		scanf_s("%d", &j);
		printf("%d\n",f(i-1, j-1,m,n ,arr));
	}
	return 0;
}
int f(int i,int j,int m,int n, int arr[][100]) {
	int fin=0;
	int a = i;
	int b = j;
	while (i != -1 && i != m && j != -1 && j != n) {
		if (arr[i][j] == 1) {
			i--;
		}
		else if (arr[i][j] == 2) {
			i++;
		}
		else if (arr[i][j] == 3) {
			j--;
		}
		else {
			j++;
		}
		if (i == a && j == b) {
			return -1;
		}
		fin += 1;
		if (fin >= 10000) {
			return -1;
		}


	}
	return fin;
}