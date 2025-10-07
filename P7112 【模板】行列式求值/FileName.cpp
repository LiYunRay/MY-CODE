#include<stdlib.h>
#include<stdio.h>
void swap(long long*, long long*);
long long a[600][600];
int n,t;
void pla(int,int);
int main(void) {
	scanf_s("%d %d", &n,&t);

	int i, j, k;
	
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			scanf_s("%d", &a[i][j]);
			a[i][j] = a[i][j] % t;
		}
	}
	long long fin = 1;
	for (i = 0; i < n - 1; i++) {
		if (a[i][i] == 0) {
			for (j = i + 1; j < n; j++) {
				if (a[j][i] != 0) {
					swap(a[i], a[j]);
					fin *= -1;
					break;

				}
			}
		}
		for (j = i; j < n; j++) {
			if (a[j][i] < 0) {
				for (k = i; k < n; k++) {
					a[j][k] = -a[j][k];
				}
				fin *= -1;
			}
		}
		for (j = i + 1; j < n; j++) {
			pla(i, j);
		}


	}
	for (i = 0; i < n; i++) {
		fin *= a[i][i];
		fin = fin % t;
	}
	if (fin < 0) {
		fin += t;
	}
	printf("%lld", fin);
	return 0;
}



void pla(int p, int q) {
	int i, j,g;
	while (a[q][p] != 0) {
		if (a[p][p] > a[q][p]) {
		    g = a[p][p] / a[q][p];
			if (a[p][p] % a[q][p] == 0) {
				for (i = p; i < n; i++) {
					a[p][i] = (a[p][i] - a[q][i] * (g-1)) % t;
				}
			}
			else {
				for (i = p; i < n; i++) {
					a[p][i] = (a[p][i] - a[q][i] * g) % t;
				}
			}
		}
		else {
			g = a[q][p] / a[p][p];
			for (i = p; i < n; i++) {
				a[q][i] = (a[q][i] - a[p][i]*g ) % t;
			}
		
		}
	}
}
void swap(long long *r, long long *b) {
	int o, i;
	for (i = 0; i < n; i++) {
		o = r[i];
		r[i] = b[i];
		b[i] = o;
	}
}