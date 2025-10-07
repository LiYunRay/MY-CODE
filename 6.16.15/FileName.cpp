#include<stdio.h>
#include<string.h>
int main(void) {
	char list[256];
	int i;
	for (i = 0; i < 256; i++) {
		list[i] = 0;
	}
	for (i = 0; i < 256; i++) {
		scanf_s("%c", &list[i]);
		if (list[i] == '\n') {
			break;
		}
	}

	int len = strlen(list);
	for (i = len-1; i >=0; i--) {
		printf("%c", list[i]);
	}
	return 0;
}