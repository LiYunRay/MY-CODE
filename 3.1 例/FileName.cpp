#include<stdio.h>
int main(void) {
	float weight, value;
	float* p_w;
	p_w = &weight;// 指针指向weight的地址

	scanf_s("%f",p_w);
	value = 1700.0 * weight * 14.5833;
	printf("%f", value);
	return 0;
}