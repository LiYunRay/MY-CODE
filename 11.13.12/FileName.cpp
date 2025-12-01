#include<stdio.h>
#include<string.h>
#include<ctype.h>
int main(void) {
	char a;
	int pla=0;
	int word,up,low,ac,num;
	int temp = 0;
	word = up = low = ac = num = 0;
	while (a = getchar()) {
		if (a == '#') {
			if (temp == 1) word += 1;
			break;
		}
		if (isdigit(a) == 4) num += 1;
		if (islower(a) == 2)low += 1;
		if (isupper(a) == 1) {
			up += 1;
			if (temp == 0) {
				temp = 1;
				word += 1;
			}
		}
		if (isalpha(a) && temp == 0) {
			temp = 1;
			word += 1;
		}
		if ((a==' ' || a == '\n') && temp == 1) temp = 0;
		if (ispunct(a) != 0) {
			ac += 1;
			temp = 0;
		}
	}
	printf("%d\n%d\n%d\n%d\n%d\n",word,up,low,ac,num);
	return 0;
}

