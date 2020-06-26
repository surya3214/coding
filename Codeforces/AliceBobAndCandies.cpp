// AC #Simple, #Implementation, #Adhoc
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
const int N_MAX = 1000;
int n, moves, s1, s2;
int candies[BUFF(N_MAX)];
void process() {
  moves = s1 = s2 = 0;
  for (int l = 1, r = n, prv = 0, running; l <= r;) {
    ++moves;
    running = 0;
    while (running <= prv && l <= r) {
      if (moves & 1)
        running += candies[l++];
      else running += candies[r--];
    }
    if (moves & 1)
      s1 += running;
    else s2 += running;
    prv = running;
  }
}
void program() {
  int tcase;
  cin >> tcase;
  while (tcase--) {
    cin >> n;
    for (int i = 1; i <= n; ++i)
      cin >> candies[i];
    process();
    cout << moves << " " << s1 << " " << s2 << endl;
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}