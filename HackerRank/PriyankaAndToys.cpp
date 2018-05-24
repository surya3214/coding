// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define W_MAX 10000
using namespace std;
typedef long long int ll;
bool present[BUFF(W_MAX)];
void program() {
  int t, n;
  int cnt = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &t);
    present[t] = true;
  }
  for (int i = 0; i <= W_MAX; ++i) {
    if (present[i]) {
      cnt++;
      i += 4;
    }
  }
  printf("%d\n", cnt);
}
int main() {
  program();
  return 0;
}