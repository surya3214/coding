// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 1000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int inp[BUFF(N_MAX)];
int n, t_time;
struct {
  int time;
  int val;
} cnt[BUFF(N_MAX)];
void reset() { ++t_time; }
void sanitizeCount(int x) {
  if (cnt[x].time != t_time) {
    cnt[x].val = 0;
    cnt[x].time = t_time;
  }
}
bool dfs(int idx) {
  if (idx == n + 1)
    return true;
  int a, b;
  a = idx - 1;
  b = n - idx;
  sanitizeCount(a);
  if (cnt[a].val) {
    --cnt[a].val;
    if (dfs(idx + 1))
      return true;
    ++cnt[a].val;
  }
  sanitizeCount(b);
  if (cnt[b].val) {
    --cnt[b].val;
    if (dfs(idx + 1))
      return true;
    ++cnt[b].val;
  }
  return false;
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &inp[i]);
      sanitizeCount(inp[i]);
      ++cnt[inp[i]].val;
    }
    if (dfs(1))
      printf("YES\n");
    else printf("NO\n");
  }
}
int main() {
  program();
  return 0;
}