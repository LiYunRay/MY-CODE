#include<stdio.h>
#include<string.h>
int f(char*, char);
int main(void) {
	char c;
	scanf_s("%c", &c,1);
	getchar();
	char arr[100];
	fgets(arr, 100, stdin);
	int fin = f(arr, c);
	if (fin != -1) {
		printf("%d\n%p", fin+1, &arr[fin - 1]);
	}
	else printf("NO");
	return 0;
}
int f(char* arr, char a) {
	int i;
	for (i = 0; i < 100; i++) {
		if (arr[i] == a) {
			break;
		}
		if (arr[i] == 0) {
			return -1;
		}
	}
	return i;
}



