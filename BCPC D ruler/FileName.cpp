#include<stdio.h>
#include<set>
#include<algorithm>
#include<vector>
using namespace std;
int main(void) {
	int t,n,i;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		vector<int> q;
		if (n == 2) q = { 1,2 };
		else {
			i = 1;
			while (i * i <= n) {
				q.push_back(i);
				i += 1;
			}
			int temp = i - 1;
			i = 2;
			while (i * temp <= n) {
				q.push_back(i * temp);
				i += 1;
			}
			if (n % temp != 0) q.push_back(n);

		}
		printf("%d\n", q.size());
		for (i = 0; i < q.size(); i++) {
			printf("%d ", q[i]);
			printf("\n");
		}
	}
	return 0;
}