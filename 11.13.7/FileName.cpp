#include<stdio.h>
#include<string.h>
char* mystrncpy(char*, char*,int);
int main(void) {
	char arr[100], brr[100];
	int n;
	scanf_s("%d", &n);
	gets_s(arr, 100);
	while (gets_s(brr, 100) ) {

		mystrncpy(arr, brr, n);
		
		puts(arr);
		puts(brr);

	}
	return 0;

}
char* mystrncpy(char* arr, char* brr, int n) {
	int i,j;
	if (strlen(brr) < n) {
		for (i = 0; i < strlen(brr); i++) arr[i] = brr[i];
		for (j = i; j < strlen(arr); j++) arr[i] = 0;
	
	}
	return arr;
}