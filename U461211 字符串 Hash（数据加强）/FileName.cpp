#include<stdio.h>
#include<string>
#include<iostream>

#include<set>
using namespace std;
using std::string;
using ll = long long;
using ull = unsigned long long;
ull base = 131;
ull mod1 = 114514191803;
ull mod2 = 1e9 + 7;
ull hash1(string s) {
	int len = s.size();
	ull ans = 0;
	for (int i = 0; i < len; i++) ans = (ans * base + (ull)s[i]) % mod1;
	return ans;
}
ull hash2(string s) {
	int len = s.size();
	ull ans = 0;
	for (int i = 0; i < len; i++) ans = (ans * base + (ull)s[i]) % mod2;
	return ans;
}
bool cmp(const string s, const string t) {
	bool f1 = hash1(s) != hash1(t);
	bool f2 = hash2(s) != hash2(t);
	return f1 || f2;
}
int main(void) {
	int n;
	scanf_s("%d", &n);
	int i,j;
	ull a, b;
	string s;
	set<pair<ull, ull>> hashset;
	getline(cin,s);
	for (i = 0; i < n; i++) {
		getline(cin, s);
		a= hash1(s);
		b= hash2(s);
		hashset.emplace(a, b);
	}
	
	printf("%d", hashset.size());
	return 0;
}