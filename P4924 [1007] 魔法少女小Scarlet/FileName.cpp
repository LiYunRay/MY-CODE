#include<stdio.h>
#include<stdlib.h>
void f( int []);
int n, m;
int** p;
int** q;
int main(void) {
	int ope[500][4];
	scanf_s("%d  %d", &n, &m);
	p = (int**)malloc(n * sizeof(int*));
	int i, j;
	for (i = 0; i < n; i++) {
		p[i]=(int*)malloc(n * sizeof(int));
	}
	for (i = 0; i < m; i++) {
		scanf_s("%d %d %d %d", &ope[i][0], &ope[i][1], &ope[i][2], &ope[i][3]);
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			p[i][j] = i * n + j + 1;
		}
	}
	for (i = 0; i < m; i++) {
		f( ope[i]);
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%d ", p[i][j]);
		}
		printf("\n");
	}
	return 0;
}
void f(int arr[4]) {
	int i, j;
	
	q = (int**)malloc(n * sizeof(int*));
	for (i = 0; i < n; i++) {
		q[i] = (int*)malloc(n * sizeof(int));
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			q[i][j] = p[i][j];
		}
	}
	for (i = arr[0] - 1 - arr[2]; i < arr[0] + arr[2]; i++) {
		for (j = arr[1] - 1 - arr[2]; j < arr[1] + arr[2]; j++) {
			if (arr[3] == 0) {
				q[j+arr[0]-arr[1]][arr[0]+arr[1]-i-2] = p[i][j];
			}
			else {
				q[arr[0] + arr[1] - j-2][-arr[0] + arr[1] + i] = p[i][j];

			}
		}
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			p[i][j] = q[i][j];
		}
	}
	for (i = 0; i < n; i++) {
		free(q[i]);
	}
	free(q);


}