// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100
using namespace std;
typedef long long int ll;
int n, k;
int flowers[BUFF(N_MAX)];
void program() {
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; i++)
    scanf("%d", &flowers[i]);
  sort(flowers + 1, flowers + 1 + n);
  ll ans = 0;
  int left = k, times = 1;
  for (int i = n; i >= 1; i--) {
    ans += times * flowers[i];
    if (!(--left)) {
      times++;
      left = k;
    }
  }
  printf("%lld\n", ans);
}
int main() {
  program();
  return 0;
}