#include<stdio.h>
int arr[1000], brr[1000], crr[1000], rank[1000];
int max(int,int);
void ex(int,int);
void f(int*);
void mul(int);
void com(void);
int n;
int temp[10005],fin[10005],all[10005];
void div(int);
int main(void) {
	scanf_s("%d", &n);
	int i, j, x, y;
	scanf_s("%d %d", &x, &y);
	for (i = 0; i < n; i++) scanf_s("%d %d", &arr[i], &brr[i]);
	for (i = 0; i < n; i++) {
		crr[i] = arr[i] * brr[i];
		rank[i] = i;
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (crr[rank[j]] > crr[rank[j + 1]]) ex(j, j + 1);
		}
	}
	for (i = 0; i < 10000; i++) all[i] = 0;
	temp[0] = x;
	for (i = 0; i < 10000; i++) {
		if (temp[i] >= 0) {
			temp[i + 1] += temp[i] / 10;
			temp[i] %= 10;
		}
	}
	div(brr[rank[0]]);
	com();
	f(arr);
	for (i = 10000; i >= 0; i--) if (all[i] != 0) break;
	if (i == -1) printf("0");
	else {
		for (j = i; j >= 0; j--) printf("%d", all[j]);
	}
	return 0;
}
void ex(int i, int j) {
	int temp;
	temp = rank[i];
	rank[i] = rank[j];
	rank[j] = temp;
}

int max(int a, int b) { return a > b ? a : b; }
void f(int* arr) {
	int i;
	for (i = 0; i < n-1 ; i++) {
		mul(arr[rank[i]]);
		div(brr[rank[i+1]]);
		com();
	}
}
void mul(int a) {
	int i;
	for (i = 0; i < 10000; i++) {
		temp[i] *= a;
	}
	for (i = 0; i < 10000; i++) {
		if (temp[i] >= 0) {
			temp[i + 1] += temp[i] / 10;
			temp[i] %= 10;
		}
	}
}

void div(int a) {
	int i,now,pla,len;
	for (i = 0; i < 10000; i++) fin[i] = 0;
	for (i = 10000; i >= 0; i--) if (temp[i] != 0) break;
	len = i;
	pla = i;
	now = 0;
	for(i = len; i >= 0; i--) {
		now = temp[i] + now * 10;
		if (now >= a) {
			fin[pla] = now / a;
			now %= a;
			pla -= 1;

		}
		else {
			fin[pla] = 0;
			pla -= 1;
		}
		if (pla < 0) break;
	}
}
void com(void) {
	int i,j;
	for (i = 10000; i >= 0; i--) {
		if (fin[i] == all[i]) continue;
		else if (fin[i] > all[i]) {
			for (j = 0; j <= i; j++) all[j] = fin[j];
			break;
		}
		else break;
	}
}