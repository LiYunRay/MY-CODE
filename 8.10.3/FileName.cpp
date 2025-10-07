#include<stdio.h>
#include<ctype.h>
int main(void) {
	int i = 0;
	char ch;
	printf("help");
	while ((ch = getchar()) != EOF) {

		if (isalpha(ch) == 1) {
			i+= 1;
		}
		else {
			continue;
		}
	}
	printf("%d ", i);
	return 0;
}