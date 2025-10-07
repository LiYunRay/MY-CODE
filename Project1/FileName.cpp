#include<stdio.h>
int main(void) {
	int T;
	scanf_s("%d", &T);
	int i,j,k,l,m;
	int n,q;
	int c;
	int name[200][20];
	int num;
	int in;
	int ans[21][20];
	int fin[20];
	for (i = 0; i < T; i++) {
		scanf_s("%d %d", &n,&q);
		scanf_s("%d", &c);
		getchar();
		for (j = 0; j < c; j++) {
			for (k = 0; k < 20; k++) {
				scanf_s("%d", &name[j][k]);
				if (name[j][k] == ' ') {
					break;
				}
			}
		}
		for (j = 0; j < q; j++) {
			scanf_s("%d", &num);
			getchar();
			for (k = 0; k < num; k++) {
				scanf_s("%d", &ans[j][k]);
				if (name[j][k] == ' ') {
					break;
				}
			}
		}
		for (j = 0; j < n; j++) {
			if (in == 1) {

			}
		}
	}
}
