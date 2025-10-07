#include<stdio.h>
int fin[200];
int len;
int  m;
long long k;
int memory[200][200][2];
short num[200];
short now[200];
int f(int,int,int);
int g(int, int);
int h(int, int);
int gf[200][200];
int main(void) {
	int i, j,p;
	scanf_s("%lld %d", &k, &m);
	for (i = 0; i < 200; i++) {
		scanf_s("%d", &num[i]);
		if (num[i] != 1 && num[i] != 0) {
			num[i] = 0;
			len = i;
			break;
		}
	}

	for (i = 0; i < 200; i++) {
		now[i] = -1;
	}
	for (i = 0; i < 200; i++) {
		for (j = 0; j < 200; j++) {
			gf[i][j] = -1;
			for (p = 0; p < 2; p++) {
				memory[i][j][p] = -1;
			}
		}
	}
	
	for (i = 1; i <=m; i++) {
		fin[i] = f(0, i,0);
	}
	printf("%d",h(1, m));
	return 0;
}
int f(int l, int m, int t) {
	int a = 0;
	if (memory[l][m][t] != -1) {
		return memory[l][m][t];
	}

	else {
		if (l < len - 1) {
			if (t == 1) {
				memory[l][m][1] = g(len - l + 1, m);
				return memory[l][m][1];
			}
			if (t == 0) {
				if (m == 0) {
					return 0;
				}
				else {
					if (num[l] == 0) {
						now[l] == 0;

						a = f(l + 1, m, 0);
						memory[l][m][0] = a;

					}
					else if (num[l] == 1) {
						now[l] = 0;
						a += f(l + 1, m, 1);
						now[l] = 1;
						a += f(l + 1, m - 1, 0);
						memory[l][m][0] = a;
					}
					now[l] = -1;
					return a;
				}
			}
		}
		else {
			if (m > 1) {
				return 0;

			}
			else if (m == 1) {
				if (t == 1) {
					return 1;
				}
				else {
					if (num[len] == 1) {
						return 1;
					}
					else {
						return 0;
					}
				}
			}
			else if (m == 0) {
				return 0;
			}
		}
	}
}
int g(int a, int b) {
	if (gf[a][b] != -1) {
		return gf[a][b];
	}
	else {
		if (b == a) {
			return 1;
		}
		else if (b > a) {
			return 0;
		}
		else {
			int i, fin = 1;
			for (i = 0; i < b; i++) {
				fin *= (a - i);
			}
			for (i = 1; i <= b; i++) {
				fin /= i;
			}
			gf[a][b] = fin;
			return fin;
		}
	}
}
int h(int i, int w) {
	int j, fina = 0;
	
		if (i == k) {
			return fin[w];
		}
		else {
			for (j = 0; j < w; j++) {
				fina += fin[j] * h(i + 1, m - j);
			}
			return fina;
		}
	
}