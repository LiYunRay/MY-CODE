#include<stdio.h>
int main(void) {
	char ch;
	int i,j = 0;
	while ((ch = getchar()) != '#') {
		if (ch == 'e') {
			i = 1;
		}
		if (ch == 'i'&& i==1) {
			i = 0;
			j += 1;

		}
	}
	printf("%d", j);
	return 0;
}