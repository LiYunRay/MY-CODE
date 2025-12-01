#include<stdio.h>
#include<queue>
#include<algorithm>
using namespace std;
using ll = long long;
#define N = 10005;
typedef struct Node {
	long long v, t;
}Node;
Node a[100005];
priority_queue<Node> q;
bool cmp(Node a, Node b) {
	return a.v > b.v;
}
int main(void) {
	ll fin = 0;
	int n;
	scanf_s("%d", &n);
	int i;
	for (i = 1; i <= n; i++) {
		scanf_s("%lld %lld", &a[i].v, &a[i].t);
	}
	sort(a + 1, a + n + 1, cmp);
	for (i = 1; i <= n; i++) {
		if (a[i].t <(ll) q.size()) {
			if (q.top().v < a[i].v) {
				fin += a[i].v - q.top().v;
				q.pop();
				q.push(a[i]);
			
			
			}
			else {
				q.push(a[i]);
				fin += a[i].v;
			}
		}
		printf("%lld", fin);
		return 0;
	}
}