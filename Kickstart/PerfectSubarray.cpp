// AC #PrefixSum, #Medium
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define mp make_pair
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
const int N_MAX = 1e5;
const int SUM_MAX = 1e5 * 1e2;
int n, p_sum, n_sum;
int in[BUFF(N_MAX)];
int seen[BUFF(2 * SUM_MAX)];
ll ans;
void reset() {
  p_sum = n_sum = ans = 0;
  memset(seen, 0, sizeof(seen));
}
void program() {
  int tcase;
  cin >> tcase;
  for (int t = 1; t <= tcase; ++t) {
    reset();
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      cin >> in[i];
      if (in[i] > 0)
        p_sum += in[i];
      else n_sum -= in[i];
    }
    ++seen[n_sum];
    for (int i = 1, running = 0; i <= n; ++i) {
      running += in[i];
      for (int j = 0; j * j <= p_sum; ++j) {
        if (n_sum + running - (j * j) >= 0)
          ans += seen[n_sum + running - (j * j)];
        else break;
      }
      ++seen[n_sum + running];
    }
    cout << "Case #" << t << ": " << ans << endl;
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  program();
  return 0;
}