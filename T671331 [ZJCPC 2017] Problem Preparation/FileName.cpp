#include<stdio.h>
void f(int);
int pai[100];
int main(void) {
	int t;
	scanf_s("%d", &t);
	int i;
	int o;
	int j, k;
	int n;
	int arr[100];
	int pai[100];
	int mina=0;
	for (i = 0; i < t; i++) {
		mina = 0;
		scanf_s("%d", &n);
		for (j = 0; j < n; j++) {
			scanf_s("%d", &arr[j]);
			pai[j] = arr[j];
		}
		
		if (n >= 10 && n <= 13 ) {
			
			for (j = 0; j < n; j++) {
				for (k = 0; k < n-1 ; k++) {
					if (pai[k] > pai[k + 1]) {
						o = pai[k + 1];
						pai[k + 1] = pai[k];
						pai[k] = o;
					}
				}
			}
			for (j = 0; j < n - 2; j++) {
				if (pai[j] - pai[j + 1] < -2 || pai[j] - pai[j + 1]>2) {
					mina += 1;
					break;
				}
			}
			if (mina == 0 && pai[0] == 1 && pai[1] == 1 && pai[n - 1] != pai[n - 2]) {
				printf("Yes\n");
			}
			else {
				printf("No\n");
			}

		
		}
		else {
			printf("No\n");
		}
	}
	return 0;
}
