// AC DP
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 300000
#define MOD 1000000007
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, p;
int starts[BUFF(N_MAX)];
ll ans;
int last_movie_here[BUFF(N_MAX)];
int total_movies[BUFF(N_MAX)];
void reset() {
  p = 1;
  ans = 0;
}
void program() {
  int tcase, l;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d %d", &n, &l);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &starts[i]);
    sort(starts + 1, starts + 1 + n);
    for (int i = 1; i <= n; ++i) {
      while (p <= i && starts[p] + l - 1 < starts[i])
        ++p;
      last_movie_here[i] = total_movies[p - 1] + 1;
      total_movies[i] = total_movies[i - 1] + last_movie_here[i];
      ans = (ans + last_movie_here[i]) % MOD;
    }
    printf("%d\n", ans);
  }
}
int main() {
  program();
  return 0;
}