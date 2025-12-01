#include<stdio.h>
#include<string.h>
void ex(char* ,char*);
int f(char*);
int main(void) {
	char arr[10][100],brr[10][100];
	int i, j;
	for (i = 0; i < 10; i++) gets_s(arr[i], 100);
	int per;
	while (scanf_s("%d", &per)) {
		if (per == 1) {
			for (i = 0; i < 10; i++) printf("%s ", arr[i]);
			printf("\n");
		}
		else if (per == 2) {
			for (i = 0; i < 10; i++)for (j = 0; j < 100; j++)brr[i][j] = 0;
			for (i = 0; i < 10; i++)for (j = 0; j < strlen(arr[i]); j++) brr[i][j] = arr[i][j];
			for (i = 0; i < 10; i++) for (j = 0; j < 9; j++) if (brr[j][0] > brr[j + 1][0]) {
				ex(brr[j], brr[j+1]);
			}
			for (i = 0; i < 10; i++) printf("%s\n", brr[i]);
		}
		else if (per == 3) {
			for (i = 0; i < 10; i++)for (j = 0; j < 100; j++)brr[i][j] = 0;
			for (i = 0; i < 10; i++)for (j = 0; j < strlen(arr[i]); j++) brr[i][j] = arr[i][j];
			for (i = 0; i < 10; i++) for (j = 0; j < 9; j++) if (strlen(brr[j]) > strlen(brr[j + 1])) {
				ex(brr[j], brr[j+1]);
			}
			for (i = 0; i < 10; i++) printf("%s\n", brr[i]);

		}
		else if (per == 4) {
			for (i = 0; i < 10; i++)for (j = 0; j < 100; j++)brr[i][j] = 0;
			for (i = 0; i < 10; i++)for (j = 0; j < strlen(arr[i]); j++) brr[i][j] = arr[i][j];
			for (i = 0; i < 10; i++) for (j = 0; j < 9; j++) if (f(brr[j]) > f(brr[j + 1])) {
				ex(brr[j], brr[j+1]);
			}
			for (i = 0; i < 10; i++) printf("%s\n", brr[i]);
			printf("\n");
		}
		else break;
	}
}
void ex(char* a, char* b) {
	int i;
	char temp[100];
	int n = strlen(a);
	for (i = 0; i < 100; i++)temp[i] = 0;
	for (i = 0; i < strlen(a); i++) temp[i] = a[i];
	for (i = 0; i < 100; i++)a[i] = 0;
	for (i = 0; i < strlen(b); i++)a[i] = b[i];
	for (i = 0; i < 100; i++)b[i] = 0;
	for (i = 0; i <n; i++)b[i] = temp[i];
}
int f(char* a) {
	int i; 
	int fin = 0;
	for (i = 0; i < strlen(a); i++) {
		if (i == ' ') break;
		fin += 1;
	}
	return fin;
}