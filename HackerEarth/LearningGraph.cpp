// AC Graph Theory Easy
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e3
#define VAL_MAX (int) N_MAX
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, m, k;
struct {
  int val;
  vector<int> friends[BUFF(VAL_MAX)];
} nodes[BUFF(N_MAX)];
struct S {
  S() {}
  S(int t_id, int t_val) : id(t_id), val(t_val) {}
  bool operator <(S t) { return val < t.val; }
  int id, val;
} s_values[BUFF(N_MAX)];
int s_ptr;
void addToSorted(int id, int val) { s_values[++s_ptr] = { id, val }; }
void compressValues() {
  sort(s_values + 1, s_values + 1 + s_ptr);
  for (int l = 1, r, val = 0; l <= s_ptr; l = r + 1) {
    for (r = l; r + 1 <= s_ptr && s_values[r + 1].val == s_values[l].val; ++r);
    ++val;
    for (int i = l; i <= r; ++i)
      nodes[s_values[i].id].val = val;
  }
}
void program() {
  int x;
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);
    addToSorted(i, x);
  }
  compressValues();
  int u, v;
  for (int i = 1; i <= m; ++i) {
    scanf("%d %d", &u, &v);
    nodes[u].friends[nodes[v].val].push_back(v);
    nodes[v].friends[nodes[u].val].push_back(u);
  }
  for (int u = 1, seen = 0, ans = -1, size; u <= n; ++u, seen = 0, ans = -1) {
    for (int j = VAL_MAX; j >= 1; --j) {
      size = nodes[u].friends[j].size();
      if (size + seen < k)
        seen += size;
      else {
        sort(nodes[u].friends[j].begin(), nodes[u].friends[j].end());
        ans = nodes[u].friends[j][size - (k - seen)];
        break;
      }
    }
    printf("%d\n", ans);
  }
}
int main() {
  program();
  return 0;
}