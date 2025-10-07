#include<stdio.h>
#include<math.h>
int num(int, int[]);
int main(void) {
	int n, arr[1001],i, fin;
	fin = 0;
	scanf_s("%d", &n);
	printf("%d", (num(n, arr)+arr[1]));
	return 0;
}


int num(int n, int arr[]) {
	int i,k,j;
	int fin = 0;
	for (i = 0; i < 1001; i++) {
		arr[i] = 0;
	}
	arr[n] = 1;
	for (k = 0; k < 3; k++) {
		for (i = n / pow(4, k); i >= 2; i--) {
			for (j = 1; j <=(i / 2); j++) {
				arr[j] += arr[i];
			}
			fin += arr[i];
			arr[i] = 0;
		}
	}
	return fin;
}