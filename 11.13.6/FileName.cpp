#include<stdio.h>
#include<string.h>
int f(char*, char);
int main(void) {
	char c;
	scanf_s("%c", &c);
	char arr[100];
<<<<<<< HEAD
	int i,n;
	scanf_s("%d", &n);
	for (i = 0; i < n; i++) {
		fgets(arr, 100, stdin);
		printf("%d", f(arr, c));

	}

=======
	fgets(arr, 100, stdin);
	int fin = f(arr, c);
>>>>>>> 3886f91172feb4c97da2dab30a2cdde14b96c08a
	
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
