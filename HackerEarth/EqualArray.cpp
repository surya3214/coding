// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
#define INF 1e15
using namespace std;
typedef long long int ll;
int elements[BUFF(N_MAX)];
ll l_sum, r_sum, x;
int n;
void reset() { x = INF; l_sum = r_sum = 0;  }
void program() {
  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; ++i) {
    reset();
    scanf("%d", &n);
    for (int j = 1; j <= n; ++j) {
      scanf("%d", &elements[j]);
      l_sum += elements[j];
    }
    l_sum -= elements[n];
    r_sum = elements[n];
    for (int j = n - 1; j >= 1; --j) {
      if (l_sum <= r_sum)
        x = min(x, r_sum - l_sum);
      l_sum -= elements[j];
      r_sum += elements[j];
    }
    if (x == INF) x = -1;
    printf("%lld\n", x);
  }
}
int main() {
  program();
  return 0;
}