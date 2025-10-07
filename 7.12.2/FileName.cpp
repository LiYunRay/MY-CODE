#include<stdio.h>
int main(void) {
	char ch;
	int a=0;
	while ((ch = getchar()) != '#') {
		printf("\"%c\" \"%d\"    ",ch,ch);
		a += 1;
		if ((a % 8) == 0) {
			printf("\n");
		}
	}
	return 0;
}