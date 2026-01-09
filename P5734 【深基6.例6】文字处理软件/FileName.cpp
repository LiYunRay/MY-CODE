#include<iostream>
#include<string>
using namespace std;
string s;
string temp;
int cp(int x) {
	if (s.size() - temp.size() < x) return -1;
	else {
		for (int i = 0; i < temp.size(); i++) {
			if (temp[i] != s[i + x]) return -1;
		}
		return 0;
	}
}
int main(void) {
	int q;
	cin >> q;
	int a, b;
	cin >>s;
	int ope;
	for (int i = 0; i < q; i++) {
		cin >> ope;
		if (ope == 1) {
			cin >> temp;
			s += temp;
			cout << s << "\n";
		}
		else if (ope == 2) {
			cin >> a;
			cin >> b;
			temp.clear();
			for (int j = a; j < a + b; j++) {
				temp += s[j];
			}
			s = temp;
			cout << s << "\n";
		}
		else if (ope == 3) {
			cin >> a;
			cin >> temp;
			string fin=s;
			s.clear();
			for (int j = 0; j < a; j++) {
				s += fin[j];
			}
			for (int j = 0; j < temp.size(); j++) {
				s += temp[j];
			}
			for (int j = a; j < fin.size(); j++) {
				s += fin[j];
			}
			cout << s<<"\n";

			
		}
		else if (ope == 4) {
			cin >> temp;
			int fin = -1;
			for (int j = 0; j < s.size(); j++) {
				if (cp(j) == 0) {
					fin = j;
					break;
				}
			}
			printf("%d\n", fin);
		}
	}
	return 0;
}