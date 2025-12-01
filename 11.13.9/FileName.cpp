#include<stdio.h>
#include<string.h>
void reverse(char*);
int main(void) {
	char arr[100];
	char* p;
	while (gets_s(arr, 100)) {
		reverse(arr);
		puts(arr);
	}
	return 0;
}
void reverse(char* arr) {
	char brr[100];
	int i;
	int n = strlen(arr);
	for (i = 0; i <n; i++) {
		brr[i] = arr[i];
	}
	for (i = n - 1; i >= 0; i--) {
		arr[n - i - 1] = brr[i];
	}
}