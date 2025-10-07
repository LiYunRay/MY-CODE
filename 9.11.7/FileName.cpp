#include<stdio.h>
int sig(char);
int main(void) {
	char ch;
	int a;
	while ((ch = getchar()) != EOF) {
		a = sig(ch);
		printf("%d\n", a);
	}
	return 0;
}
int sig(char ch) {
	if (ch <= 122 && ch >= 97) {
		return(ch - 32);
	}
	else if (ch >= 65 && ch <= 90) {
		return(ch);
	}
	else {
		return -1;
	}
}