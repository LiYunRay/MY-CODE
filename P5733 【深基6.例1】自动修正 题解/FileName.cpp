#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;
int main(void) {
	string s;
	cin >> s;
	for (int i = 0; i < s.size(); i++) if (s[i] >= 'a' && s[i] <= 'z') s[i] += 'A'-'a';
	cout << s;
	return 0;

}