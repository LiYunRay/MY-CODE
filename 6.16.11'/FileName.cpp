#include<stdio.h>
int main(void)
{
	int numbers[8];
	int x, y;
	printf("ÇëÊäÈë8¸öÊı£º");
	for (x = 0; x < 8; x++) {
		scanf_s("%d ", &numbers[x]);
		printf("%d ", numbers[x] );
	}
	for (y = 7; y >= 0; y--)
		printf("%d ", numbers[y]);
	return 0;
}