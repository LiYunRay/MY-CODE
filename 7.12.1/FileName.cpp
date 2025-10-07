#include<stdio.h>
int main(void) {
	char ch;
	int space, next,other;
	space = next=other=0;
	while ((ch = getchar()) != '#') {
		if (ch == ' ') {
			space += 1;
		}
		else if (ch == '\n') {
			next += 1;
		}
		else {
			other += 1;
		}
	}
	printf("%d %d %d", space, next, other);
	return 0;
}