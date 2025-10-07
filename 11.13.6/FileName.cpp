#include<stdio.h>
#include<string.h>
int f(char*, char);
int main(void) {
	char c;
	scanf_s("%c", &c);
	char arr[100];
	fgets(arr, 100, stdin);
	int fin = f(arr, c);
	
	return 0;
}
int f(char* arr, char a) {
	int i;
	for (i = 0; i < 100; i++) {
		if (arr[i] == a) {
			break;
		}
		if (arr[i] == 0) {
			return 0;
		}
	}
	return 1;
}
