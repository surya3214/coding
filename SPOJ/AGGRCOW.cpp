// AC Binary search
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, cows;
int fences[BUFF(N_MAX)];
int getMid(int l, int r) { return l + (r - l) / 2; }
bool isPossible(int x) {
  int k, last_chosen;
  last_chosen = 1;
  k = cows - 1;
  for (int i = 2; i <= n; ++i) {
    if (fences[i] - fences[last_chosen] >= x) {
      last_chosen = i;
      --k;
      if (k == 0) return true;
    }
  }
  return false;
}
int findBS() {
  int l, r, mid;
  l = 1e9;
  r = fences[n] - fences[1];
  for (int i = 2; i <= n; ++i)
    l = min(l, fences[i] - fences[i - 1]);
  while (l <= r) {
    mid = getMid(l, r);
    if (isPossible(mid))
      l = mid + 1;
    else r = mid - 1;
  }
  return l - 1;
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d %d", &n, &cows);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &fences[i]);
    sort(fences + 1, fences + 1 + n);
    printf("%d\n", findBS());
  }
}
int main() {
  program();
  return 0;
}