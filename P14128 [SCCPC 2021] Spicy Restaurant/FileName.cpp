#include<stdio.h>
#include<queue>
#include<vector>
#define MAXN 100005
#define MAXM 1000005
#define MAXC 105

#define inf 10000005
using namespace std;
int spi[MAXN];
vector<int> arr[MAXN];
queue<int> t;
int dist[MAXN][MAXC];
int main(void) {
	int i;
	int n, m, q;
	scanf_s("%d %d %d", &n, &m, &q);
	for (i = 1; i <= n; i++) scanf_s("%d", &spi[i]);
	int u, v;
	for (i = 0; i < m; i++) {
		scanf_s("%d %d", &u, &v);
		arr[u].push_back(v);
		arr[v].push_back(u);
	}
	int j,x;
	for (i = 1; i <= 100; i++) {
		for (j = 1; j <= n; j++) dist[j][i] = inf;
		for (j = 1; j <= n; j++) {
			if (spi[j] <= i) {
				dist[j][i] = 0;
				t.push(j);
			}
		}
		while (!t.empty()) {
			u = t.front();
			t.pop();
			for (j = 0; j < arr[u].size(); j++) {
				v = arr[u][j];
				if (dist[v][i] > dist[u][i] + 1) {
					dist[v][i] = dist[u][i] + 1;
					t.push(v);
				}
			}

		}
		for (j = 1; j <= n; j++)  if (dist[j][i] == inf) dist[j][i] = -1;


	}
	int a, b;
	for (i = 0; i < q; i++) {
		scanf_s("%d %d", &a,& b);
		printf("%d\n", dist[a][b]);
	}
	return 0;
}
