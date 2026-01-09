#include<iostream>
#include<string>
using namespace std;
int a = 0, b = 0;
int f(int a) {
	if (a == 'b') return 'o';
	else if (a == 'o') return 'y';
	else if (a == 'y') return NULL;
	else if (a == 'g') return 'i';
	else if (a == 'i') return 'r';
	else if (a == 'r') return 'l';
	else if (a == 'l') return NULL;
	else return NULL;
}
void g(int x) {
	if (x == 'b' || x == 'o' || x == 'y') a += 1;
	if (x == 'g' || x == 'i' || x == 'r' || x == 'l') b += 1;
}
int main(void) {
	string s;
	cin >> s;
	int top = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '.') {
			if (top != 0) {
				g(top);
				top = 0;
			}
			continue;
		}
		if (top != 0) {
			if (s[i] != f(top)) {
				g(top);
			}
		}
		if (s[i] != '.') top = s[i];
	}
	if (top != 0) g(top);
	cout << a << '\n';
	cout << b;
	return 0;
}