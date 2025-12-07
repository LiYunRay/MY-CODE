#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<unordered_set>
#include<unordered_map>
const int mod = 123456789;
using namespace std;
unordered_map<int,int> cou;
unordered_set<int> s;
vector<int> v;
int main(void) {
	int n;
	scanf("%d", &n);
	int temp;
	int i;
	for (i = 0; i < n; i++) {
		scanf("%d", &temp);
		s.insert(temp);
		cou[temp] += 1;
	}
	int end=-1;
	while (true) {
		if (s.count(end + 1)) end += 1;
		else break;
	}
	vector<long long> pow2(n + 1, 1);
	for (i = 1; i <= n; i++) {
		pow2[i] = pow2[i - 1] * 2 % mod;
	}
	vector<long long> f(end + 2, 1);
	for (int k = 1; k <= end + 1; k++) {
		i=k - 1;
		long long t = (pow2[cou[i]] - 1 + mod) % mod;
		f[k] = f[k - 1] * t % mod;
	}
	long long fin = 0;
	for (int i = 0; i <= end; i++) {
		fin = (fin + f[i]) % mod;
	}
	printf("%lld", fin);
	return 0;
	

}