#include<stdio.h>
#include<string.h>
void f(char*);
int main(void) {
	char arr[100];
	while (gets_s(arr, 100)) {
		f(arr);
		puts(arr);
	}
	return 0;

}
void f(char arr[100]) {
	int n = strlen(arr);
	char brr[100];

	int i,pla=0;
	for (i = 0; i < 100; i++)brr[i] = 0;
	for (i = 0; i < n; i++) {
		if (arr[i] == ' ') continue;
		brr[pla] = arr[i];
		pla += 1;
	}
	for (i = 0; i < n; i++) arr[i] = 0;
	for (i = 0; i < strlen(brr); i++)arr[i] = brr[i];
}