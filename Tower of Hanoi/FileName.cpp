#include<stdio.h>
void hanoi(int,int,int);
int els(int, int);
int main(void) {
	int scale;
	printf("please input the  scale of  the hanoi tower\n");
	scanf_s("%d", &scale);
	hanoi(scale,1,3);
	return 0;
}

void hanoi(int a,int m,int n) {
	int mid = els(m, n);
	if (a > 1) {
		hanoi(a - 1, m, mid);
		hanoi(1, m, n);
		hanoi(a - 1, mid, n);
	}
    if (a==1){
		printf("%d,%d\n", m, n);
	}

}

int els(int a, int b) {
	int c;
	if (a == 1 && b == 2) {
		c = 3;
	}
	else if (a == 1 && b == 3) {
		c = 2;
	}
	else if (a == 2 && b == 1) {
		c = 3;
	}
	else if (a == 2 && b == 3) {
		c = 1;
	}
	else if (a == 3 && b == 1) {
		c = 2;
	}
	else if (a == 3 && b == 2) {
		c = 1;
	}
	return c;
}

