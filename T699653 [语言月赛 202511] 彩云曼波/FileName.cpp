#include<stdio.h>
void per(int);
int arr[8];
int n;
int found = 0;
int main(void) {
	scanf_s("%d", &n);
	int i;
	for (i = 0; i < n; i++) arr[i] = i + 1;
	per(0);
	return 0;
}
void per(int i) {
	int j;
	if (found == 1) return;
	if (i == n) {
		for (i = 0; i < n; i++) {
			printf("%d", arr[i]);
			if(i<n-1) printf(" ");
		}
		printf("\n");
		fflush(stdout);
		int res=0;
		scanf_s("%d", &res);
		if (res == 1) {
			found = 1;
			return;
		}
	}
	else {
		for (j = i; j < n; j++) {
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			per(i + 1);
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}

}