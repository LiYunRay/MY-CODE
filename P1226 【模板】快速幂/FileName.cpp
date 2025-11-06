#include<stdio.h>
int arr[31];
long long fin[31];
int main(void) {
	int a, b, p,i,temp,num,max;
	scanf_s("%d %d %d", &a, &b, &p);
	fin[0] = a;
	for (i = 0; i < 31; i++) {
		arr[i] = 0;
	}
	temp = b;
	num = 0;
	while (temp >= 1) {
		if (temp % 2 == 1) {
			arr[num] = 1;
		}
		temp = temp / 2;
		num += 1;
	}
	for (i = 30; i >= 0; i--) {
		if (arr[i] != 0) {
			break;
		}
	}
	max = i;
	long long out;
	out = 1;
	for (i = 1; i <=max; i++) {
		fin[i] = fin[i - 1] * fin[i - 1]%p;
	}
	for (i = 0; i <=max; i++) {
		if (arr[i] == 1) {
			out *= fin[i];
			out = out % p;
		}
	}
	printf("%d^%d mod %d=%lld", a, b, p, out);
	return 0;
}
