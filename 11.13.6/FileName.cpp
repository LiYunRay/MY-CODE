#include<stdio.h>
#include<string.h>
int is_within(char*, char);
int main(void) {
	char arr[100];
	char brr[100];
	gets_s(brr, 100);
	gets_s(arr, 100);
	int i;
	for (i = 0; i < strlen(brr); i++) {
		printf("%c %d\n",brr[i],is_within(arr, brr[i]));
	}
	return 0;
	
}
int is_within(char* arr, char c) {
	int len = strlen(arr);
	int i;
	int fin=0;
	for (i = 0; i < len; i++) {
		if (arr[i] == c) {
			fin = 1;
			break;
		}
	}
	return fin;
}
