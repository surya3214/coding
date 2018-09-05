// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 8
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int sums[BUFF(N_MAX)];
bool hates[BUFF(N_MAX)][BUFF(N_MAX)];
bool taken[BUFF(N_MAX)];
void markHates(int u, int v) { hates[u][v] = true; }
struct {
  bool set;
  int val;
} ans;
void updateAns(int x) {
  if (ans.set)
    ans.val = max(ans.val, x);
  else {
    ans.val = x;
    ans.set = true;
  }
}
void compute(int cur_sum) {
  updateAns(cur_sum);
  bool go_further;
  for (int i = 1; i <= N_MAX; ++i) {
    if (!taken[i]) {
      go_further = true;
      for (int j = 1; j <= N_MAX; ++j) {
        if (i != j && taken[j] && hates[i][j]) {
          go_further = false;
          break;
        }
      }
      if (go_further) {
        taken[i] = true;
        compute(cur_sum + sums[i]);
        taken[i] = false;
      }
    }
  }
}
void program() {
  int q, u, v;
  for (int i = 1; i <= N_MAX; ++i)
    scanf("%d", &sums[i]);
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d", &u, &v);
    markHates(u, v);
    markHates(v, u);
  }
  compute(0);
  printf("%d\n", ans.val);
}
int main() {
  program();
  return 0;
}