#include<iostream>
#include<string>
using namespace std;
int main(void) {
	string s;
	getline(cin, s);
	int fin = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] != ' ' && s[i] != '\n') fin += 1;
	}
	printf("%d", fin);
	return 0;
}