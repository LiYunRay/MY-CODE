#include<stdio.h>
int main(void) {
	int ch;
	int i = 0;
	while ((ch = getchar()) != '#') {
		switch (ch) {
		case '!': {
			printf("!!");
			i += 1;
			break;
		}
		case '.': {
			printf("!");
			i += 1;
			break;
		}
		default: {
			putchar(ch);
			break;
		}
		}

	}
	printf("\n%d", i);
	return 0;
}