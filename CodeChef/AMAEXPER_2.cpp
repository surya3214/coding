// TLE
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;
#define mx 5001
vector<int> adj[mx];
vector<int> cost[mx];
int dist[mx][mx];
int l[mx], r[mx];
int A[mx];
int counter = 0;
void root(int x, int p) { // (1, -1)
	l[x] = ++counter;
	A[l[x]] = x;
	int sz = adj[x].size();
	for (int i = 0;i < sz;++i) {
		if (adj[x][i] == p)continue;
		root(adj[x][i], x);

	}
	r[x] = counter;
}
void dfs(int x, int p, int d,int ox) {
	int sz = adj[x].size();
	dist[x][ox] = d;
	for (int i = 0;i < sz;++i) {
		if (adj[x][i] == p)continue;
		dfs(adj[x][i], x, d + cost[x][i], ox);
	}
}
int solve(int x) {
	
	int ans = (1 << 30);
	for (int i = l[x];i <= r[x];++i) {
		int cur = 0;
		for (int j = l[x];j <= r[x];++j)
			cur = max(cur, dist[A[i]][A[j]]);
		ans = min(ans, cur);
	}
	return ans;

}
int main() {
	int n;
	int t;
	cin>>t;
	while(t--){
	
	cin >> n;
	for(int i=0;i<=n;++i)
	adj[i].clear(), cost[i].clear();
	counter =0;
	
	for (int i = 0;i < n - 1;++i) {
		int u, v, val;
		scanf("%d%d%d", &u, &v, &val);
		adj[u].push_back(v);
		adj[v].push_back(u);
		cost[u].push_back(val);
		cost[v].push_back(val);
	}
	root(1, -1);
	for (int i = 1;i <= n;++i)
		dfs(i, -1, 0, i);
	for (int i = 1;i <= n;++i)
		printf("%d\n", solve(i));
	}
}