// AC Trie, Prefix-Suffix matching
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define mp make_pair
#define N_MAX (int) 1e5
#define CHILD_MAX 710
#define NODES_MAX (int) (N_MAX * 3)
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
int n, root;
ll ans;
struct N {
  int count;
  int child[BUFF(CHILD_MAX)];
} nodes[BUFF(NODES_MAX)];
int nodes_ptr;
int getNodes() {
  ++nodes_ptr;
  nodes[nodes_ptr].count = 0;
  for (int i = 0; i < CHILD_MAX; ++i)
    nodes[nodes_ptr].child[i] = 0;
  return nodes_ptr;
}
void reset() {
  nodes_ptr = ans = 0;
  root = getNodes();
}
void pushToTrie(vector<int> &rep) {
  int cur = root;
  for (int i = 0; i < rep.size(); ++i) {
    if (!nodes[cur].child[rep[i]])
      nodes[cur].child[rep[i]] = getNodes();
    cur = nodes[cur].child[rep[i]];
  }
  ++nodes[cur].count;
}
void queryTrie(int cur, int lvl) {
  for (int i = 0, next; i < CHILD_MAX; ++i) {
    next = nodes[cur].child[i];
    if (next) {
      queryTrie(next, lvl + 1);
      nodes[cur].count += nodes[next].count;
    }
  }
  if (nodes[cur].count >= 2) {
    int times = nodes[cur].count / 2;
    ans += 1LL * times * lvl * lvl;
    nodes[cur].count = nodes[cur].count & 1;
  }
}
void program() {
  reset();
  cin >> n;
  string s, t;
  for (int i = 1; i <= n; ++i) {
    cin >> s;
    t = s;
    reverse(begin(t), end(t));
    vector<int> rep(s.size());
    for (int i = 0; s[i]; ++i)
      rep[i] = (s[i] - 'a' + 1) * 26 + (t[i] - 'a' + 1);
    pushToTrie(rep);
  }
  queryTrie(root, 0);
  cout << ans << endl;
}
int main() {
  ios::sync_with_stdio(0);
	cin.tie(0);
  cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  int tcase;
  cin >> tcase;
  while (tcase--)
    program();
  return 0;
}