#include<stdio.h>
#include<string.h>
char* string_in(char*, char*);
int main(void) {
	char arr[100];
	char brr[100];
	gets_s(arr, 100);
	char* p;
	while (gets_s(brr, 100)) {
		p = string_in(arr, brr);
		printf("%p\n", p);

	}
	return 0;
}
char* string_in(char* arr, char*brr) {
	int i, j, fin = 0;
	int temp = 0;
	for (i = 0; i < strlen(arr); i++) {
		temp = 0;
		for (j = 0; j < strlen(brr); j++) {
			if (strlen(arr) - i < strlen(brr)) break;
			if (arr[j+i] != brr[j]) break;
			temp += 1;
		}
		if (temp == strlen(brr)) {
			return arr + i;
		}
	}
	return NULL;

}