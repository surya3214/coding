// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) (5e5)
#define NODES_MAX (int) (8 * N_MAX * log2(N_MAX))
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
int n;
int input[BUFF(N_MAX)];
struct N {
  int l, r, last;
  N(int l, int r, int last) : l(l), r(r), last(last) {}
  N() {}
} nodes[BUFF(NODES_MAX)];
int nodes_ptr;
int roots[BUFF(N_MAX)];
void program() {
  int q;
  scanf("%d", &n);
  map<int, int> last;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &input[i]);
  }
  scanf("%d", &q);
  for (int i = 1, l, r; i <= q; ++i) {
    scanf("%d %d", &l, &r);
  }
}
int main() {
#ifndef ONLINE_JUDGE
  // freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}