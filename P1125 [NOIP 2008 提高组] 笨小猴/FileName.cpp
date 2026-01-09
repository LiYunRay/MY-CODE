#include<stdio.h>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
int max(int a, int b) {
	return a > b ? a : b;
}
int min(int a, int b) {
	return a > b ? b : a;
}
int p(int a) {
	int i = 2;
	if (a == 2||a==3) return 1;
	while (i * i < a) {
		if (a % i == 0) return 1;
		i++;
	}
	return 0;
}
int main(void) {
	string s;
	cin >> s;
	int m = -1, n = 1000;
	int temp;
	for (int i = 0; i <27; i++) {
		temp = count(s.begin(), s.end(), 'a' + i);
		if (temp >= 1)m = max(m, temp), n = min(temp, n);
		
	}

	if (p(m - n) == 1) printf("Lucky Word\n"), printf("%d", m - n);
	else printf("No Answer\n"), printf("0");

}
