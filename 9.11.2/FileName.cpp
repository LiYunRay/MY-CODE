#include<stdio.h>
void chline(char, int, int);
int main(void) {
	char ch;
	int i, j;
	scanf_s("%c", &ch);
	scanf_s("%d %d", &i, &j);
	chline(ch, i, j);
	return 0;
}
void chline(char ch, int a, int b) {
	int m,n;
	for (m = 1; m <= a; m++) {
		for (n = 1; n <= b; n++) {
			printf("%c", ch);
		}
		printf("\n");
	}
}