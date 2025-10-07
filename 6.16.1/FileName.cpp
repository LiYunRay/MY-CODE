#include<stdio.h>
int main(void) {
	char letter[26];
	int i,j;
	for (j = 0, i = 'a'; i <= 'a' + 25; i++,j++) {
		letter[j] = i;
	}
	for (i = 0; i <= 25; i++) {
		printf("%c", letter[i]);
	}
	return 0;
}