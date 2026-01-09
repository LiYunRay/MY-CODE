#include<iostream>
#include<string>
using namespace std;
int f(string s) {
	int fin = 1;
	for (int i = 0; i < s.size(); i++) {
		fin *= (s[i]-'A'+1);
		fin %= 47;
	}
	return fin;
}
int main(void) {
	string s;
	string t;
	cin >> s;
	cin >> t;
	if (f(s) == f(t)) {
		cout << "GO";
	}
	else cout << "STAY";
	return 0;
}