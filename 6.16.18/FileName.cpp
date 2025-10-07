#include<stdio.h>
int main(void) {
	int a,i ;
	a = 5;
	for (i = 1; a <= 150; i++) {
		a = (a - i) * 2;
		printf("%d\n", a);
	}
	return 0;
}