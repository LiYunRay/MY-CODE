#include<stdio.h>
void jolly(void);
void deny(void);//����Ҫʹ�õĺ���һ��Ҫ�������ȶ���


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