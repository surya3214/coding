// AC #Easy, #Implementation
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
const int N_MAX = 100;
const int INF = 1e9;
int dp[BUFF(N_MAX)];
void program() {
  int n;
  cin >> n;
  for (int i = 1, x; i <= n; ++i) {
    cin >> x;
    if (x)
      dp[i] = INF;
    else {
      if (i == 1)
        dp[i] = 0;
      else dp[i] = min(dp[i - 1] + 1, (i - 2 >= 1) ? dp[i - 2] + 1: INF);
    }
  }
  cout << dp[n] << endl;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
#ifdef SURYA
  freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}
