// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 1000
using namespace std;
typedef long long int ll;
int n, k;
int a[BUFF(N_MAX)], b[BUFF(N_MAX)];
void program() {
  int q, t;
  scanf("%d", &q);
  while (q--) {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
      scanf("%d", &t);
      a[i] = k - t;
    }
    for (int i = 1; i <= n; i++)
      scanf("%d", &b[i]);
    sort(a + 1, a + 1 + n);
    sort(b + 1, b + 1 + n);
    for (t = 1; t <= n; t++)
      if (!(b[t] >= a[t])) break;
    printf("%s\n", (t == n + 1) ? "YES" : "NO");
  }
}
int main() {
  program();
  return 0;
}