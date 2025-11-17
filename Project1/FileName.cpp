#include<stdio.h>
<<<<<<< HEAD
#include<stdlib.h>
#include<string.h>
char input[400000];
long long alines[100000];
long long blines[100000];
int main(void) {
	unsigned long long n;
	scanf_s("%llu", &n);
	unsigned long long j;
	for (j = 0; j < n; j++) {
		scanf_s("%lld", &alines[j]);
	}

	for (j = 0; j < n; j++) {
		scanf_s("%lld", &blines[j]);
	}

	for (j = 0; j < 400000; j++) {
		if ((scanf_s("%c", &input[j])) != 1) {
			break;
		}
		else {
			scanf_s("%c", &input[j]);
		}
	}

	unsigned long long size;
	size = strlen(input);
	for (j = size - 1; j >= 0; j--) {
		if ((input[j] == ']') && (input[j - 1] == ']')) {
			continue;
		}
	}
}
=======
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
>>>>>>> 3886f91172feb4c97da2dab30a2cdde14b96c08a
