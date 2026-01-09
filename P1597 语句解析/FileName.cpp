#include<iostream>
#include<string>
using namespace std;
int main(void) {
	string s;
	cin >> s;
	int a = 0, b = 0, c = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] >= 'a' && s[i] <= 'c') {
			if (s[i + 3] >= '1' && s[i + 3] <= '9') {
				if (s[i] == 'a') a = s[i + 3] - '1' + 1;
				if (s[i] == 'b') b = s[i + 3] - '1' + 1;
				if (s[i] == 'c') c = s[i + 3] - '1' + 1;
			}
			else if (s[i + 3] >= 'a' && s[i + 3] <= 'c') {
				if (s[i] == 'a') {
					if (s[i + 3] == 'a') a = a;
					if (s[i + 3] == 'b') a = b;
					if (s[i + 3] == 'c') a = c;
				}
				if (s[i] == 'b') {
					if (s[i + 3] == 'a') b = a;
					if (s[i + 3] == 'b') b = b;
					if (s[i + 3] == 'c') b = c;
				}
				if (s[i] == 'c') {
					if (s[i + 3] == 'a') c = a;
					if (s[i + 3] == 'b') c = b;
					if (s[i + 3] == 'c') c = c;
				}
			}
		}
	}
	cout << a << ' ' << b << ' ' << c;
	return 0;
}