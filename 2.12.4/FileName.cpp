#include<stdio.h>
void jolly(void);
void deny(void);//对于要使用的函数一定要进行事先定义


int main(void) {
	jolly();
	jolly();
	jolly();
	deny();
	return 0;
}
void jolly(void) {
	printf("For he is a jolly good fellow\n");
}
void deny(void) {
	printf("Which body can deny!");
}