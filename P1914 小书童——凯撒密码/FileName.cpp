#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;
int main(void) {
	int n;
	scanf_s("%d", &n);
	string s;
	cin >> s;
	int temp;
	for (int i = 0; i < s.size(); i++) {
		temp = s[i] - 'a';
		temp += n;
		temp %= 26;
		s[i] = temp + 'a';
	}
	cout << s;
	return 0;
}