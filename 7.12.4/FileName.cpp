#include<stdio.h>
int main(void) {
	char ch;
	int i=0;
	while ((ch = getchar()) != '#') {
		if (ch == '.') {
			printf("!");
			i += 1;
		}
		else if (ch == '!') {
			printf("!!");
			i += 1;
		}
		else {
			putchar(ch);
		}

	}
	printf("\n%d", i);
	return 0;
}