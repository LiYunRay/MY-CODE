#include<stdio.h>
void f(int, int,int mo[][8],int*final);
int main(void) {
	int mo[8][8];
	int i, j;
	int final = 0;
	for (i = 0; i<8; i++) {
		for (j = 0; j<8; j++) {
			mo[i][j] = 0;
		}
	}
	for (i = 0; i < 8; i++) {
		f(0, i, mo, &final);

	}
	printf("%d\n", final);
	return 0;
}
void f(int a, int b, int mo[][8], int* k) {
	int i, j;
	if (a < 7) {
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (mo[i][j] >= (a + 1)) {
					mo[i][j] = 0;
				}
			}
		}
		if (mo[a][b] == 0) {
			for (i = 0; i < 8; i++) {
				if (mo[a][i] == 0) {
					mo[a][i] = (a + 1);
				}
			}
			for (i = 0; i < 8; i++) {
				if (mo[i][b] == 0) {
					mo[i][b] = a + 1;
				}
			}
			for (i = 0; (a + i) < 8 && (b + i) < 8; i++) {
				if (mo[a + i][b + i] == 0) {
					mo[a + i][b + i] = a + 1;
				}
			}
			for (i = 0; (a - i) >= 0 && (b - i) >=0; i++) {
				if (mo[a - i][b - i] == 0) {
					mo[a - i][b - i] = a + 1;
				}
			}
			for (i = 0; (a + i) < 8 && (b - i) >= 0; i++) {
				if (mo[a + i][b - i] == 0) {
					mo[a + i][b - i] = a + 1;
				}
			}
			for (i = 0; (a - i) >= 0 && (b + i) < 8; i++) {
				if (mo[a - i][b + i] == 0) {
					mo[a - i][b + i] = a + 1;
				}
			}
			for (i = 0; i < 8; i++) {
				f(a + 1, i, mo, k);
			}
		}
	}
	if (a == 7) {
		if (mo[a][b] == 0) {
			*k += 1;
		}
	}
}