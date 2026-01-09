#include<iostream>
#include<string>
using namespace std;
int main(void) {
	string s;
	getline(cin, s);
	int fin = 0;
	int temp;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] >= 'a' && s[i] <= 'r') {
			temp = (s[i] - 'a' + 1) % 3;
			if (temp == 0) temp = 3;
		}
		else if (s[i] == 's' || s[i] == 'z') temp = 4;
		else if (s[i] >= 't' && s[i] <= 'y') {
			temp = (s[i] - 't' + 1) % 3;
			if (temp == 0) temp = 3;
		}
		else temp = 1;
		fin += temp;

	}
	cout << fin;
	return 0;
}