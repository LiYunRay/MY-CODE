#include<stdio.h>
#include<string.h>
void f(char*);
int main(void) {
	char arr[100];
	int i;
	for (i = 0; i < 100;  i++) {
		arr[i] = 0;
	}
	f(arr);
	fputs(arr,stdout);
	return 0;
}
void f(char* arr) {
	int i;
	int temp;
 	for (i = 0;; i++) {
		temp = getchar();
		if (temp != ' ' && temp != '\n') {
			arr[0] = temp; 
			break;
		}
	}
	for (i = 1; i < 100; i++) {
		arr[i] = getchar();
		if (arr[i] == ' ' || arr[i] == '\n')
			break;
	}

}