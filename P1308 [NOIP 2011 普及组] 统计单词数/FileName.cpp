#include<iostream>
#include<string>
using namespace std;
string target;
string s;
string temp;
int cpm(void) {
	if (target.size() != temp.size()) return -1;
	else {
		for (int i = 0; i < temp.size(); i++) {
			if (temp[i] != target[i])return -1;
		}
		return 0;
	}
}

int main(void) {
	cin >> target;
	getchar();
	getline(cin, s);
	for (int i = 0; i < target.size(); i++) {
		if (target[i] >= 'A' && target[i] <= 'Z') target[i] = target[i] - 'A' + 'a';
	}for (int i = 0; i < s.size(); i++) {
		if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] - 'A' + 'a';
	}
	int first = -1, fin = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ' ' || i == s.size() - 1) {
			if (cpm() == 0) {
				if (first == -1) first = i-temp.size();
				fin += 1;
			}
			temp.clear();
		}
		else {
			temp += s[i];
		}
	}
	if (fin == 0) printf("-1");
	else {
		printf("%d %d", fin, first);
	}
	return 0;
}