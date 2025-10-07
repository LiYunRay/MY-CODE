#include<stdio.h>
#include<string.h>
void f(char *, int);
int main(void) {
	char arr[100];
	int i;

	for (i = 0; i < 100; i++) {
		arr[i] = 0;
	}
	int n;
	scanf_s("%d", &n);
	getchar();
	f(arr,n);
	fputs(arr, stdout);
	return 0;
}
void(f(char* arr, int n)) {
	int i;
	for (i = 0; i < n; i++) {
		arr[i] = getchar();
	}
}
