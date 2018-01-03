// AC - BIT + Descending sort
#include <bits/stdc++.h>
#define N_MAX 30010
#define Q_MAX 200010
using namespace std;
struct Q {
  int l, r, k, idx;
} Query[N_MAX + Q_MAX];
int n, q;
int BIT[N_MAX], ans[Q_MAX];
bool comparator(Q a, Q b) {
  if (a.k != b.k)
    return a.k > b.k;
  if (a.l != -1)
    return true;
  else if (b.l != -1)
    return false;
  return true;
}
int getSumBIT(int idx) {
  int sum = 0;
   while (idx > 0) {
     sum += BIT[idx];
     idx = idx - (idx & -idx);
   }
   return sum;
}
void updateBIT(int idx, int val) {
  while (idx <= n) {
    BIT[idx]++;
    idx = idx + (idx & -idx);
  }
}
void solve() {
  for (int i = 1; i <= (n + q); i++) {
    if (Query[i].l != -1) // Query
      ans[Query[i].idx] = getSumBIT(Query[i].r) - getSumBIT(Query[i].l - 1);
    else updateBIT(Query[i].idx, Query[i].k); // BIT
  }
}
void program() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &Query[i].k);
    Query[i].idx = i;
    Query[i].l = Query[i].r = -1;
  }
  scanf("%d", &q);
  for (int i = n + 1; i <= (n + q); i++) {
    scanf("%d %d %d", &Query[i].l, &Query[i].r, &Query[i].k);
    Query[i].idx = i - n;
  }
  sort(Query + 1, Query + 1 + n + q, comparator);
  solve();
  for (int i = 1; i <= q; i++)
    printf("%d\n", ans[i]);
}
int main() {
  program();
  return 0;
}