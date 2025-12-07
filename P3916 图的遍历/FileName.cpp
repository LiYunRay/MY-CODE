#include<stdio.h>
#include<queue>
#include<vector>
using namespace std;
int A[100005];
vector<int> arr[100005];
queue<int> t;
int u, v;

void bfs(int x) {
	int i;
	A[x] = x;
	t.push(x);
	while (!t.empty()) {
		u = t.front();
		t.pop();
		for (i = 0; i < arr[u].size(); i++) {
			v = arr[u][i];
			if (A[v] == -1) {
				A[v] = x;
				t.push(v);
			}
		}
	}
}
int main(void) {
	int i, j;
	int k;
	int n, m;
	scanf_s("%d %d", &n, &m);
	for (i = 0; i < m; i++) {
		scanf_s("%d %d", &v, &u);
		arr[u].push_back(v);
	}
	for (i = 1; i <= n; i++)A[i] = -1;
	for (i = n; i > 0; i--) {
		if (A[i] == -1) {
			bfs(i);
		}
	}
	for (i = 1; i <= n; i++) printf("%d ", A[i]);
	return 0;
}
