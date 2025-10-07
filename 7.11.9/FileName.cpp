#include<stdio.h>
int main(void) {
	char ch;
	while ((ch = getchar()) != '#') {
		if (ch == '\n') {
			continue;
		}
		printf("step1\n");
		if (ch == 'c') {
			continue;
		}
		else if (ch == 'b') {
			break;
		}
		else if (ch == 'h')
			goto laststep;
		printf("step2\n");
	laststep:printf("step3\n");
	}
	printf("done\n");
	return 0;
	
}