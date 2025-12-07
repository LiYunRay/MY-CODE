#include<stdio.h>
#include<queue>
#include<stdlib.h>
typedef struct edge {
	int u, v;
}edge;
std::queue<int> per;
edge arr[1000005];
int n, m;
int a[100005];
int rank[100005];
void dfs(int t) {
	if (a[t] == 1) return;
	else {
		a[t] = 1;
		printf("%d ", t);
		if (rank[t] == -1) return;
		else {
			int i=rank[t];
			while (arr[i].u == t) {
				dfs(arr[i].v);
				i += 1;
			}
		}
	}
	
}

void bfs(int t) {
	per.push(t);
	while (per.size() != 0) {
		int temp = per.front();
		per.pop();

		a[temp] = 1;
		printf("%d ", temp);
		if (rank[temp] == -1) continue;
		else {
			int i = rank[temp];
			while (arr[i].u == temp) {
				if (a[arr[i].v] != 1) per.push(arr[i].v);
				a[arr[i].v] = 1;
				i += 1;
			}
		}
	}
}
int cmp(const void* c,const void* d) {
	edge* a = (edge*)c;
	edge* b = (edge*)d;
	if (a->u != b->u) {
		return a->u - b->u;
	}
	else {
		return a->v - b->v;
	}
}
int main(void) {
	scanf_s("%d %d", &n, &m);
	int i;
	for (int i = 1; i <= n; i++) a[i] = 0;
	for (i = 1; i <=m; i++) scanf_s("%d %d", &arr[i].u, &arr[i].v);
	qsort(arr + 1, m, sizeof(edge), cmp);
	for (i = 1; i <= n; i++) rank[i] =-1;
	rank[1] = 1;
	for (i = 1; i < m; i++) {
		if (arr[i].u != arr[i + 1].u) rank[arr[i + 1].u] = i + 1;
	}
	dfs(1);
	for (int i = 1; i <= n; i++) a[i] = 0;
	printf("\n");
	bfs(1);
	return 0;


}