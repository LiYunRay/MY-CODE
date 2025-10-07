#include<stdio.h>
int main(void) {
	char ch;
	while ((ch = getchar())!='#') {
		switch (ch) {
		case '\n':
			break;
		case 'q':
			printf("step1\nstep2\nstep3\n");
			break;
		case'c':
			printf("step1\n");
			break;
		case'h':
			printf("step1\nstep3\n");
			break;
		}
		if (ch == 'b') {
			printf("step1\n");
			break;
		}
	}
	printf("done");
	return 0;
}