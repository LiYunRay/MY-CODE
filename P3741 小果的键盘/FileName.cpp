#include<iostream>
#include<string>
using namespace std;
int main(void) {
	string s;
	int n;
	cin >> n;
	cin >> s;
	int fin = 0;
	int a = 0;
	for (int i = 0; i < n - 1; i++) {
		if (s[i] == 'V' && s[i + 1] == 'K') fin += 1;

	}
	for (int i = 1; i < n - 1; i++) {
		if (s[i - 1] != 'V' && s[i] == 'K' && s[i + 1] == 'K') {
			a = 1;
		}
	}
	for (int i = 0; i < n - 2; i++) {
		if (s[i] == 'V' && s[i + 1] == 'V' && s[i + 2] == 'V') a = 1;

	}
	if (s[n - 1] == 'V' && s[n - 2] == 'V')a = 1;
	if (s[0] == 'K' && s[1] == 'K')a = 1;

	fin += a;
	cout << fin;
	return 0;
}