#include<iostream>
#include<string>
using namespace std;
int arr[30];
int main(void) {
	string s;
	for (int i = 0; i < 30; i++)arr[i] = 0;
	for (int q = 0; q < 4; q++) {
		getline(cin, s);

		for (int i = 0; i < s.size(); i++) {
			if (s[i] >= 'A' && s[i] <= 'Z') arr[s[i] - 'A' + 1] += 1;
		}
	}
	int max=-1;
	for (int i = 0; i < 30; i++) {
		max = max > arr[i] ? max : arr[i];
	}
	int end[5000];
	for (int i = 1; i <= max; i++) {
		for (int j = 26; j >= 1; j--) {
			if (arr[j] >= i) {
				end[i] = j;
				break;
			}
		}
	}
	for (int i = 0; i < max; i++) {
		for (int j = 1; j <= end[max-i]; j++) {
			if (arr[j] >= max - i)putchar('*');
			else putchar(' ');
			if (j != end[max - i])putchar(' ');
		}
		putchar('\n');
	}
	for (int i = 0; i < 26; i++) {
		putchar('A' + i);
		if (i != 25) putchar(' ');
	}
	return 0;
}