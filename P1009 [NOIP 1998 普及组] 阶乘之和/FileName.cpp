#include<stdio.h>
void f(int);
int arr[50][100];
void plus(int[], int[]);
int main(void) {
	int i,j;
	int n;
	int num[100];
	for (i = 0; i < 50; i++) {
		for (j = 0; j < 100; j++) {
			arr[i][j] = 0;
		}

	}
	for (i = 0; i < 100; i++) {
		num[i] = 0;
	}
	arr[0][0] = 1;
	scanf_s("%d", &n);
	for (i = 2; i <= n; i++) {
		f(i);
	}
	for (i = 0; i < n; i++) {
		plus(num, arr[i]);
	}
	
	for (i = 99; i >= 0; i--) {
		if (num[i] != 0) {
			break;
		}
	}
    int len = i;
	for (i = len; i >= 0; i--) {                                                                                                                                                                                                                        
		printf("%d", num[i]);
	}
	return 0;
	
}
void f(int a) {
	int i;
	for (i = 99; i >= 0; i--) {
		if (arr[a - 2][i] != 0)
		{
			break;
		}
	}
	int len = i;
	for (i = 0; i <=len; i++) {
		arr[a - 1][i] = arr[a - 2][i] * a;
	}
	for (i = 0; i < 99 ; i++) {
		arr[a - 1][i + 1] += arr[a - 1][i] / 10;
		arr[a - 1][i] = arr[a - 1][i] % 10;
	}

}
void plus(int num[100], int arr[100]) {
	int i;
	for (i = 0; i < 100; i++) {
		num[i] += arr[i];
	}
	for (i = 0; i < 99; i++) {
		if (num[i] >= 10) {
			num[i + 1] += num[i] / 10;
			num[i] = num[i] % 10;
		}

	}
}
	
