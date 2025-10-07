#include<stdio.h>
void f(void);
int main(void) {
	f();
	f();
	f();
	printf("\n");
	f(); 
	f();
	printf("\n");
	f();
	return 0;
}

void f(void) {
	printf("Smile!");
}