// TLE
#include <iostream>
#include <cstdio>
#define N_MAX 100010
using namespace std;
int n, p, ans;
int citizen_groups[N_MAX], cg_n;
int groups[N_MAX];
int groups_memoized[N_MAX];
int ranks[N_MAX];
bool finished[N_MAX];
void reset() {
  for (int i = 0; i < N_MAX; i++)
    groups[i] = -1, ranks[i] = 1;
}
int findGroup(int u) {
  if (groups[u] == -1)
    return u;
  return findGroup(groups[u]);
}
void groupify(int u, int v) {
  int u_p = findGroup(u);
  int v_p = findGroup(v);
  if (u_p != v_p) {
    if (ranks[u_p] >= ranks[v_p]) {
      groups[v_p] = groups[v] = u_p;
      ranks[u_p] += ranks[v_p];
    } else {
      groups[u_p] = groups[u] = v_p;
      ranks[v_p] += ranks[u_p];
    }
  }
}
void memoize() {
  for (int i = 0; i < n; i++)
    groups_memoized[i] = findGroup(i);
}
void compute() {
  for (int i = 0; i < cg_n; i++)
    for (int j = i + 1; j < cg_n; j++)
      ans += citizen_groups[i] * citizen_groups[j];
}
void program() {
  int u, v;
  scanf("%d %d", &n, &p);
  reset();
  while (p--) {
    scanf("%d %d", &u, &v);
    groupify(u, v);
  }
  int i_p;
  memoize();
  for (int i = 0; i < n; i++) {
    i_p = groups_memoized[i];
    if (!finished[i_p]) {
      finished[i_p] = true;
      citizen_groups[cg_n++] = ranks[i_p];
    }
  }
  compute();
  printf("%d\n", ans);
}
int main() {
  program();
  return 0;
}