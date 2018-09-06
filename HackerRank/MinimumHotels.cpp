// AC Simulation Adhoc
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 10000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int positions[BUFF(N_MAX)];
int n, k;
int hotel_at, cnt;
void reset() {
  hotel_at = cnt = 0;
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &positions[i]);
    scanf("%d", &k);
    sort(positions + 1, positions + 1 + n);
    for (int i = 1; i <= n; ++i) {
      if (!hotel_at || (positions[i] > hotel_at && positions[i] - hotel_at > k)) {
        ++cnt;
        hotel_at = positions[i] + k;
      }
    }
    printf("%d\n", cnt);
  }
}
int main() {
  program();
  return 0;
}