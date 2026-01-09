#include<iostream>
#include<string>
using namespace std;
int f(string s) {

	int fin = 0;

	for (int i = 0; i < s.size(); i++) {
		fin *= 10;
		fin += s[i] - '1' + 1;

	}
	return fin;


}
int g(int a) {
	int fin = 0;
	if (a == 0) return 1;
	while (a != 0) {
		a /=10;
		fin += 1;
	}
	return fin;
}
int main(void) {
	int n;
	cin >> n;
	string temp;
	int ope = -1;
	int a, b;
	for (int i = 0; i < n; i++) {
		cin >> temp;

		if (temp[0] >= 'a' && temp[0] <= 'c') {
			ope = temp[0] - 'a' + 1;
			cin >> temp;
			a = f(temp);
			cin >> temp;
			b = f(temp);
			
		}
		else {
			a = f(temp);
			cin >> temp;
			b = f(temp);
		}
		if (ope == 1) {
			printf("%d+%d=%d\n", a, b, a + b);
			printf("%d\n", g(a) + g(b) + g(a + b) + 2);
		}
		if (ope == 2) {
			printf("%d-%d=%d\n", a, b, a - b);
			if(a-b>=0) printf("%d\n", g(a) + g(b) + g(a - b) + 2);
			else printf("%d\n", g(a) + g(b) + g(a - b) + 3);
		}
		if (ope == 3) {
			printf("%d*%d=%d\n", a, b, a * b);
			printf("%d\n", g(a) + g(b) + g(a * b) + 2);
		}
	}
	return 0;
}