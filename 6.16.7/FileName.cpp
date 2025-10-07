#include<stdio.h>
#include<string.h>
int main(void) {
	char word[30];
	scanf_s("%s", word, 30);
	int a = strlen(word);
	int i;
	for (i = 1; i <= a; i++) {
		printf("%c", word[a - i]);
	}
	return 0;
}