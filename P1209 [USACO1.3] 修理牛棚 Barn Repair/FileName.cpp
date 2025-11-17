#include<stdio.h>
int arr[200];
int all[200];
void sort(int*);
void ex(int, int);
int main(void) {
	int m, s, c;
	scanf_s("%d %d %d", &m, &s, &c);
	int t=0;
	int tf = 0;
	int temp=0;
	int i;
	int fin = 0;
	int rank = 0;
	for (i = 0; i < s; i++) arr[i] = 0;
	for (i = 0; i < 200; i++)all[i] = 0;
	for (i = 0; i < c; i++) {
		scanf_s("%d", &t);
		arr[t - 1] = 1;
	}
	for (i = 0; i < s; i++) {
		if (arr[i] == 1) {
			all[rank] = temp;
			rank += 1;
			temp = 0;
			tf = 1;
		}
		else if (arr[i] == 0 && tf == 1) {
			temp += 1;
			tf = 0;
		}
		else if (arr[i] == 0) temp += 1;
	}
	all[0] = 0;
	int l=0;
	for (i = 0; i < s; i++) {
		if (arr[i] == 1) break;
		l+= 1;
	}
	for (i = s-1; i >=0; i--) {
		if (arr[i] == 1) break;
		l+=1;
	}
	
	sort(all);
	for (i = 0; i < m-1; i++) l += all[i];
	fin = s - l;
	
	printf("%d", fin);
	return 0;
}
void sort(int a[200]) {
	int i, j;
	for (i = 199; i >=0; i--) {
		for (j = i; j>=0; j--) {
			if (a[j] < a[j+1]) {
				ex(j, j + 1);
			}
		}
	}
}
void ex(int i, int j) {
	int temp;
	temp = all[i];
	all[i] = all[j];
	all[j] = temp;
}
