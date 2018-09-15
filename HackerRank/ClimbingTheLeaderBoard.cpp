// AC Binary Search
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) (2 * 1e5)
#define VAL_MAX 1e9
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int leaderboard[BUFF(N_MAX)];
int l_ptr;
int n;
int getMid(int l, int r) { return l + (r - l) / 2; }
int getRank(int x) {
  int l, r, mid;
  l = 1, r = l_ptr;
  while (l <= r) {
    mid = getMid(l, r);
    if (leaderboard[mid] <= x)
      r = mid - 1;
    else l = mid + 1;
  }
  return r;
}
void program() {
  int m;
  int x;
  scanf("%d", &n);
  leaderboard[++l_ptr] = BUFF(VAL_MAX);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);
    if (leaderboard[l_ptr] != x)
      leaderboard[++l_ptr] = x;
  }
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &x);
    printf("%d\n", getRank(x));
  }
}
int main() {
  program();
  return 0;
}